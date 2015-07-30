#include "virtualconcierge.h"
#include "ui_virtualconcierge.h"
#include <QDebug>
#include <QFileDialog>
#include <QStringList>
#include <QSurfaceFormat>
#include "SMTP/smtp.h"

VirtualConcierge::VirtualConcierge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VirtualConcierge)
{
    ui->setupUi(this);
    load_interface("VirtualConcierge/nodes.pvc","VirtualConcierge/directories.dir");
    connect(this,SIGNAL(find_path(int,int)), ui->openGLWidget ,SLOT(find_path(int,int)));
    create_interface();
}

void VirtualConcierge::get_button_value(int value,bool findvalue){
    // 0 is the starting position
    if(!findvalue)
    emit find_path(0,value);
    else show_new_interface(value);
}

void VirtualConcierge::show_new_interface(int value){

      // resizes temp array, but does not release memory!!
     this->temp.resize(0);

      // hide the buttons from the first page
      foreach(NodeButton *button,this->catagory)
          button->hide();
      foreach(NodeButton *button,this->buttons)
          button->hide();
      foreach (NodeButton *button,this->directories)
          button->hide();

      // add child directories
      if(value <this->directory_list.count()){
          QStringList dir_ls = this->directory_list.value(value).split(";");
          const int count = dir_ls.count();
          for(int x= 0;x<count;x++){
             int dir_index = dir_ls[x]!=""?dir_ls[x].toInt():(-1);
              if(dir_index > -1) {
                  NodeButton *button =this->directories.value(dir_index);
                  button->show();
                 this->temp.push_back(button);
              }
          }
      }

      // add child path locations
      if(value <this->node_list.count()){
          QStringList node_ls = this->node_list.value(value).split(";");
          const int count = node_ls.count();
          for(int y= 0;y<count;y++){
             int node_index = (node_ls[y]!="")?node_ls[y].toInt():(-1);
              if(node_index > -1) {
                  int index_from_list = get_index_from_index(this->buttons,node_index);
                  if(index_from_list > -1){
                      NodeButton *button =this->buttons.value(index_from_list);
                      button->show();
                     this->temp.push_back(button);
                    }
              }
          }
      }
      create_interface();
}

int VirtualConcierge::get_index_from_index(QVector<NodeButton* > list,int index){
    int temp = -1;
    for(int l = 0;l < list.count();l++)
        list.value(l)->getIndex()==index?temp = l: temp=temp;

    return temp;
}

void VirtualConcierge::create_interface(){
//    NodeButton *button = new NodeButton(ui->widget_directory);
    const int width = 150, height = 32;
    // reconstruct the directories
    for(int k = 0; k <this->catagory.count();k++)
       this->catagory.value(k)->setGeometry(0,k*height,width,height);

    // reconstruct temp buttons
    for( int z = 0; z <this->temp.count(); z++)
       this->temp.value(z)->setGeometry(0,z*height,width,height);

}

void VirtualConcierge::load_interface(QString filename, QString filename_directories){
    // whenever the directories file does not exist, just add some buttons

    // load the text file
    QFile textfile(filename);

    // open the text file
    textfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ascread(&textfile);

        if(textfile.isOpen()){
            // read each line of the file
            QString line = ascread.readLine();

            while(!line.isNull()){
                // break the line up in usable parts
                QStringList list = line.split(",");

                // check the type of line
                /* n-> node
                 * j-> join
                 */
                if(list[0]=="n"){
                    QString name ="";
                    int index = 0, add = 0;
                    name=list[5];
                    QTextStream(&list[6])>>add;
                    QTextStream(&list[1])>>index;
                    if(add==1){
                        NodeButton *button = new NodeButton(ui->widget_directory);
                        button->setText(name);
                        button->setIndex(index);
                        button->setGeometry(1,this->buttons.count()*(button->height()+1),button->width(),button->height());
                        PremisesExporter::fileExists(filename_directories) ? button->hide() : button->show();
                        connect(button,SIGNAL(clicked_index(int,bool)), this ,SLOT(get_button_value(int,bool)));
                       this->buttons.push_back(button);
                    }

                }
                // read next line
               line = ascread.readLine();
            }

            // close the textfile
            textfile.close();
        }

        if(PremisesExporter::fileExists(filename_directories)){
            // clear directory list
           this->directory_list.clear();
           this->node_list.clear();
           this->catagory.clear();
           this->directories.clear();
            // load the text file
            QFile textfile_directories(filename_directories);

            // open the text file
            textfile_directories.open(QIODevice::ReadOnly | QIODevice::Text);
            QTextStream ascread(&textfile_directories);

            if(textfile_directories.isOpen()){
                // read each line of the file
                QString line = ascread.readLine();
                int count_top = 0;
                while(!line.isNull()){
                    // break the line up in usable parts
                    QStringList list = line.split(",");

                    if(list[0]=="dd"){
                        QStringList dir = list[1].split(":");
                        QString name = dir.count() > 1 ? dir[1] : list[1];
                        int index = list[2].toInt();

                        NodeButton *button = new NodeButton(ui->widget_directory);
                        button->setText(name);
                        button->setIndex(index);
                        button->setDirectory(dir.count() > 1);
                        button->setGeometry(1,this->catagory.count()*(button->height()+1),button->width(),button->height());
                        connect(button,SIGNAL(clicked_index(int,bool)), this ,SLOT(get_button_value(int,bool)));
                       this->catagory.push_back(button);
                      }
                    else if(list[0]=="dl"){
                       this->directory_list.append(list[3]);
                       this->node_list.append(list[2]);
                    } else if(list[0] == "d") {

                        QStringList dir = list[1].split(":");
                        QString name = dir.count() > 1 ? dir[1] : list[1];
                        NodeButton *button = new NodeButton(ui->widget_directory);
                        button->setText(name);
                        button->setIndex(count_top);
                        button->setDirectory(dir.count() > 1);
                        button->setGeometry(1,this->directories.count()*(button->height()+1),button->width(),button->height());
                        connect(button,SIGNAL(clicked_index(int,bool)), this ,SLOT(get_button_value(int,bool)));
                        button->hide();
                       this->directories.push_back(button);
                        count_top++;
                    }

                    // read next line
                   line = ascread.readLine();
                }

                // close the textfile
                textfile_directories.close();
            }
        }
}

void VirtualConcierge::on_pushButton_send_mail_clicked(){

    //QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg *.jpeg)");
    QImage img =ui->openGLWidget->grabFramebuffer();
    //format.setSamples(4);
   // ui->openGLWidget->context()->setFormat(format);
    img.save("FloorPlan.jpg");
    //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    Smtp* smtp = new Smtp("virtualconcierge@yahoo.com", "sel_foon@1", "smtp.mail.yahoo.com",465, 30000);
    QStringList ls;
    ls.append("FloorPlan.jpg");
    smtp->sendMail("virtualconcierge@yahoo.com",ui->lineEdit_email->text() , "This is a subject", "This is a body",ls);

}

VirtualConcierge::~VirtualConcierge(){
    delete ui;
}
