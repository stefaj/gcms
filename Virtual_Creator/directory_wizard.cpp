#include "directory_wizard.h"
#include "ui_directory_wizard.h"
#include "./Functions/premises_exporter.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Directory_Wizard::Directory_Wizard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Directory_Wizard)
{
    this->directories.clear();
    this->directorylist.clear();
    this->display.clear();
    ui->setupUi(this);
    ui->button_back->hide();

    load_directories("VirtualConcierge/directories.dir");
    load_nodes("VirtualConcierge/nodes.pvc");
}

Directory_Wizard::~Directory_Wizard()
{
    delete ui;
}

void Directory_Wizard::add_this_directory_to_other() {
 for ( int z = 0 ; z < ui->listWidget_diretories_that_include->count(); z++) {
     QStringList list = ui->listWidget_diretories_that_include->item(z)->text().split(",");
     if (list.count() > 1) {
       int index = list[1].toInt();

       if (index > -1 && index < directories.count()) {
         if ( directorylist.value(index).at(directorylist.value(index).count() - 1) != ',')
           directorylist.replace(index, directorylist.value(index) + ";" + QString::number(directories.count() - 1 ));
         else
           directorylist.replace(index, directorylist.value(index) + QString::number(directories.count() - 1 ));
       }
     }
 }
 if ( ui->checkBox->isChecked() ) {
     this->display.append("DIR:" + ui->lineEdit->text() + "," + QString::number(directories.count() - 1 ));
 }
}

void Directory_Wizard::add_directory_list() {
  QString nodes, directories;
  // add the list of directories and nodes to the new directory
  for ( int k = 0; k < ui->listWidget_nodes_directories_cate->count(); k++) {
      QStringList index = ui->listWidget_nodes_directories_cate->item(k)->text().split(",");
      QString check;
      if ( index.count() > 1) {
        if(ui->listWidget_nodes_directories_cate->item(k)->text().length() > 3)
          check = ui->listWidget_nodes_directories_cate->item(k)->text().mid(0, 4);
        if(check == "DIR:") {
          directories += index[1] + ";";
        } else {
          nodes += index[1] + ";";
        }
      }
  }
  // remove the last ;
  nodes.remove(nodes.length()-1, 1);
  directories.remove(directories.length()-1, 1);

  // nodes and directories to list
  directorylist.append(QString::number(directorylist.count()) + "," + nodes + "," + directories);
}

void Directory_Wizard::on_buttonCancel_clicked() {
    this->close();
}

void Directory_Wizard::on_buttonNext_clicked() {
  if ( ui->stackedWidget->currentIndex() > 0) {
      ui->button_back->show();
  }
  // go to next wizard item
  if ( ui->stackedWidget->count() > ui->stackedWidget->currentIndex() + 1 )
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
  else {
    add_directory_list();
    add_this_directory_to_other();
    PremisesExporter::export_directories(directories, directorylist, display, "directories.dir");
    this->close();
  }

  if ( ui->stackedWidget->count() - 2 < ui->stackedWidget->currentIndex() )
    ui->buttonNext->setText("Finish");
  if ( ui->stackedWidget->currentIndex() == 2 ) {
    this->directories.append("DIR:" + ui->lineEdit->text());
  }
}

void Directory_Wizard::load_directories(QString filename) {
    // clear the list of nodes
    ui->listWidget_nodes_directories->clear();
    ui->listWidget_nodes_directories_cate->clear();

    // load the text file
    QFile textfile(filename);

    // open the text file
    textfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ascread(&textfile);

    if ( textfile.isOpen() ) {
        // read each line of the file
        QString line = ascread.readLine();

        int count_top = 0;
        while ( !line.isNull() ) {
          // break the line up in usable parts
          QStringList list = line.split(",");

          // check the type of line
          if ( list[0] == "d" ) {
            ui->listWidget_nodes_directories->addItem(list[1] + "," + QString::number(count_top));
            ui->listWidget_other_way->addItem(list[1] + "," + QString::number(count_top));
            directories.append(list[1]);
            count_top++;
          } else if ( list[0] == "dl" ) {
            directorylist.append(list[1] + "," + list[2] + "," + list[3]);
          } else if ( list[0] == "dd" ) {
            display.append(list[1] + "," + list[2]);
          }
          // read next line
          line = ascread.readLine();
        }
        // close the textfile
        textfile.close();
    }
}

void Directory_Wizard::load_nodes(QString filename) {
    // load the text file
    QFile textfile(filename);

    // open the text file
    textfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ascread(&textfile);
    // clear the nodes
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
                    ui->listWidget_nodes_directories->addItem(
                                name +
                                "," +
                                QString::number(index));
                }
            }
            // read next line
           line = ascread.readLine();
        }
        // close the textfile
        textfile.close();
    }
}

void Directory_Wizard::on_button_add_clicked() {
    if ( ui->listWidget_nodes_directories->selectedItems().count() > 0 ) {
      QString ls =
      ui->listWidget_nodes_directories->currentItem()->text();
      ui->listWidget_nodes_directories_cate->addItem(ls);
    }
}

void Directory_Wizard::on_button_remove_clicked() {
    if ( ui->listWidget_nodes_directories_cate->selectedItems().count() > 0 ) {
        QListWidgetItem *item =  ui->listWidget_nodes_directories_cate->currentItem();
        if ( item->isSelected())
            delete item;
    }
}

void Directory_Wizard::on_button_add_2_clicked() {
    if ( ui->listWidget_other_way->selectedItems().count() > 0 ) {
      QString ls =
      ui->listWidget_other_way->currentItem()->text();
      ui->listWidget_diretories_that_include->addItem(ls);
    }
}

void Directory_Wizard::on_button_remove_2_clicked() {
    if ( ui->listWidget_diretories_that_include->selectedItems().count() > 0 ) {
        QListWidgetItem *item =  ui->listWidget_diretories_that_include->currentItem();
        if ( item->isSelected())
            delete item;
    }
}

void Directory_Wizard::on_button_back_clicked() {
  if ( ui->stackedWidget->currentIndex() > 0 ) {
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
  }
}
