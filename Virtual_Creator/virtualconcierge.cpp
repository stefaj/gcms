/* Copyright 2015 Ruan Luies */

#include <QDebug>
#include <QFileDialog>
#include <QStringList>
#include <QSurfaceFormat>
#include "./virtualconcierge.h"
#include "./ui_virtualconcierge.h"
#include "./SMTP/smtp.h"

VirtualConcierge::VirtualConcierge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VirtualConcierge),
    show_email(false),
    show_access(false){
    ui->setupUi(this);
    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap(":/BackGround_Virtual_Concierge")))));
    setPalette(*palette);
    load_interface("VirtualConcierge/nodes.pvc",
                   "VirtualConcierge/directories.dir");
    connect(this, SIGNAL(find_path(int, int)),
            ui->openGLWidget, SLOT(find_path(int, int)));
    connect(this, SIGNAL(send_access(bool,bool,bool,bool)),
            ui->openGLWidget, SLOT(receive_access(bool,bool,bool,bool)));
    create_interface();


    load_config("config.config");
}

void VirtualConcierge::load_config(QString file_name) {
    if ( PremisesExporter::fileExists("VirtualConcierge/" + file_name) ) {

      // load the text file
      QFile textfile("VirtualConcierge/" + file_name);
      // open the text file
      textfile.open(QIODevice::ReadOnly | QIODevice::Text);
      QTextStream ascread(&textfile);

      if ( textfile.isOpen() ) {
        // read each line of the file
        QString line = ascread.readLine();
        while ( !line.isNull() ) {
          // break the line up in usable parts
          QStringList list = line.split("=");

          // check the type of line
          if ( list[0] == "email" ) {
            QString result = "no";

            // add email access
            if ( list.count() > 1 )
            result = list[1];
            if ( result == "yes") {
              show_email = true;
            }
          } else if ( list[0] == "accessibility" ) {
              QString result = "no";

              // add email access
              if ( list.count() > 1 )
              result = list[1];
              if ( result == "yes") {
                show_access = true;
              }
            } else if ( list[0] == "name" ) {
            QString result = "";

            // add email access
            if ( list.count() > 1 )
            result = list[1];
            ui->label_name->setText(result);
          }

        // read next line
        line = ascread.readLine();
        }

        // close the textfile
        textfile.close();
      }
    }
    if ( !show_email ) {
        ui->lineEdit_email->hide();
        ui->pushButton_send_mail->hide();
    } else {
        ui->lineEdit_email->show();
        ui->pushButton_send_mail->show();
    }

    if ( !show_access ) {
        ui->button_bicycle->hide();
        ui->button_feet->hide();
        ui->button_other_vehicle->hide();
        ui->button_wheelchair->hide();
    } else {
        ui->button_bicycle->show();
        ui->button_feet->show();
        ui->button_other_vehicle->show();
        ui->button_wheelchair->show();
    }
}

void VirtualConcierge::get_button_value(int value, bool findvalue) {
    // 0 is the starting position
    if ( !findvalue )
        emit find_path(0, value);
    else
        show_new_interface(value);
}

void VirtualConcierge::show_new_interface(int value) {
      // resizes temp array, but does not release memory!!
     this->temp.resize(0);

      // hide the buttons from the first page
      foreach(NodeButton* button, this->catagory_)
          button->hide();
      foreach(NodeButton* button, this->buttons_)
          button->hide();
      foreach(NodeButton* button, this->directories_)
          button->hide();

      // add child path locations
      if ( value < this->node_list_.count() ) {
          QStringList node_ls = this->node_list_.value(value).split(";");
          const int count = node_ls.count();
          for ( int y = 0; y < count; y++ ) {
             int node_index = (node_ls[y] != "") ? node_ls[y].toInt() : (-1);
              if ( node_index > -1 ) {
                  int index_from_list =
                          get_index_from_index(this->buttons_, node_index);
                  if ( index_from_list > -1 ) {
                      NodeButton* button =
                              this->buttons_.value(index_from_list);
                      button->show();
                     this->temp.push_back(button);
                    }
              }
          }
      }

      // add child directories
      if ( value < this->directory_list_.count() ) {
          QStringList dir_ls = this->directory_list_.value(value).split(";");
          const int count = dir_ls.count();
          for ( int x = 0; x < count; x++ ) {
             int dir_index = dir_ls[x] != "" ? dir_ls[x].toInt() : (-1);
              if ( dir_index > -1 ) {
                  NodeButton* button = this->directories_.value(dir_index);
                  button->show();
                 this->temp.push_back(button);
              }
          }
      }
      create_interface();
}

int VirtualConcierge::get_index_from_index(QVector<NodeButton* > list,
                                           int index) {
    int temp = -1;
    for ( int l = 0; l < list.count(); l++ )
        list.value(l)->getIndex() == index ? temp = l : temp = temp;

    return temp;
}

void VirtualConcierge::create_interface() {
    const int width = 256, height = 48;
    // reconstruct the directories_
    for ( int k = 0; k < this->catagory_.count(); k++ )
       this->catagory_.value(k)->setGeometry(0,
                                            k * (height+5),
                                            width,
                                            height);

    // reconstruct temp buttons
    for (  int z = 0; z <this->temp.count(); z++ )
       this->temp.value(z)->setGeometry(0,
                                        z *  (height+5),
                                        width,
                                        height);
}

void VirtualConcierge::load_interface(QString filename,
                                      QString filename_directories_) {
    // whenever the directories_ file does not exist, just add some buttons_

    // load the text file
    QFile textfile(filename);

    // open the text file
    textfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ascread(&textfile);

        if ( textfile.isOpen() ) {
            // read each line of the file
            QString line = ascread.readLine();

            while ( !line.isNull() ) {
                // break the line up in usable parts
                QStringList list = line.split(",");

                // check the type of line
                /* n-> node
                 * j-> join
                 */
                if ( list[0] == "n" ) {
                    QString name ="";
                    int index = 0, add = 0;
                    name = list[5];
                    QTextStream(&list[6]) >> add;
                    QTextStream(&list[1]) >> index;
                    if ( add == 1 ) {
                        NodeButton *button =
                                new NodeButton(ui->widget_directory);
                        button->setText(name);
                        button->setIndex(index);
                        button->setGeometry(
                                    1,
                                    this->buttons_.count() *
                                    (button->height() + 1),
                                    button->width(),
                                    button->height());
                        PremisesExporter::fileExists(filename_directories_) ?
                                    button->hide() : button->show();
                        connect(button, SIGNAL(clicked_index(int, bool)),
                                this, SLOT(get_button_value(int, bool)));
                       this->buttons_.push_back(button);
                    }
                }
                // read next line
               line = ascread.readLine();
            }

            // close the textfile
            textfile.close();
        }

        if ( PremisesExporter::fileExists(filename_directories_) ) {
            // clear directory list
           this->directory_list_.clear();
           this->node_list_.clear();
           this->catagory_.clear();
           this->directories_.clear();
            // load the text file
            QFile textfile_directories_(filename_directories_);

            // open the text file
            textfile_directories_.open(QIODevice::ReadOnly | QIODevice::Text);
            QTextStream ascread(&textfile_directories_);

            if ( textfile_directories_.isOpen() ) {
                // read each line of the file
                QString line = ascread.readLine();
                int count_top = 0;
                while ( !line.isNull() ) {
                    // break the line up in usable parts
                    QStringList list = line.split(",");

                    if ( list[0] == "dd" ) {
                        QStringList dir = list[1].split(":");
                        QString name = dir.count() > 1 ? dir[1] : list[1];
                        int index = list[2].toInt();
                        NodeButton *button =
                                new NodeButton(ui->widget_directory);
                        button->setText(name);
                        button->setIndex(index);
                        button->setDirectory(dir.count() > 1);
                        button->setGeometry(
                                    1,
                                    this->catagory_.count() *
                                    (button->height() + 1),
                                    button->width(),
                                    button->height());
                       connect(button, SIGNAL(clicked_index(int, bool)),
                               this, SLOT(get_button_value(int, bool)));
                       this->catagory_.push_back(button);
                    } else if ( list[0] == "dl" ) {
                           this->directory_list_.append(list[3]);
                           this->node_list_.append(list[2]);
                    } else if ( list[0] == "d" ) {
                        QStringList dir = list[1].split(":");
                        QString name = dir.count() > 1 ?
                                    dir[1] : list[1];
                        NodeButton *button =
                                new NodeButton(ui->widget_directory);
                        button->setText(name);
                        button->setIndex(count_top);
                        button->setDirectory(dir.count() > 1);
                        button->setGeometry(
                                    1,
                                    this->directories_.count() *
                                    (button->height() + 1),
                                    button->width(),
                                    button->height());
                        connect(button, SIGNAL(clicked_index(int, bool)),
                                this, SLOT(get_button_value(int, bool)));
                        button->hide();
                       this->directories_.push_back(button);
                        count_top++;
                    }

                    // read next line
                   line = ascread.readLine();
                }

                // close the textfile
                textfile_directories_.close();
            }
        }
}

void VirtualConcierge::on_pushButton_send_mail_clicked() {
    QImage img = ui->openGLWidget->grabFramebuffer();
    img.save("FloorPlan.jpg");
    Smtp* smtp = new Smtp("virtualconcierge@yahoo.com",
                          "sel_foon@1",
                          "smtp.mail.yahoo.com",
                          465,
                          30000);
    QStringList ls;
    ls.append("FloorPlan.jpg");
    smtp->sendMail("virtualconcierge@yahoo.com",
                   ui->lineEdit_email->text(),
                   "This is a subject",
                   "This is a body",
                   ls);
}

VirtualConcierge::~VirtualConcierge() {
    delete ui;
}

void VirtualConcierge::on_button_wheelchair_clicked() {
    emit send_access(ui->button_wheelchair->isChecked(),
                     ui->button_feet->isChecked(),
                     ui->button_bicycle->isChecked(),
                     ui->button_other_vehicle->isChecked());
}

void VirtualConcierge::on_button_feet_clicked(){
    emit send_access(ui->button_wheelchair->isChecked(),
                     ui->button_feet->isChecked(),
                     ui->button_bicycle->isChecked(),
                     ui->button_other_vehicle->isChecked());
}

void VirtualConcierge::on_button_bicycle_clicked() {
    emit send_access(ui->button_wheelchair->isChecked(),
                     ui->button_feet->isChecked(),
                     ui->button_bicycle->isChecked(),
                     ui->button_other_vehicle->isChecked());
}

void VirtualConcierge::on_button_other_vehicle_clicked() {
    emit send_access(ui->button_wheelchair->isChecked(),
                     ui->button_feet->isChecked(),
                     ui->button_bicycle->isChecked(),
                     ui->button_other_vehicle->isChecked());
}
