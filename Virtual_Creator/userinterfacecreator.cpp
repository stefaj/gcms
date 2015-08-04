/* Copyright 2015 Ruan Luies */
#include <QDebug>
#include "./userinterfacecreator.h"
#include "./ui_userinterfacecreator.h"
#include "Functions/premises_exporter.h"

UserInterfaceCreator::UserInterfaceCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserInterfaceCreator) {
    ui->setupUi(this);
    // Set the number of columns in the tree
    ui->treeWidget->setColumnCount(2);

    // Set the headers
    ui->treeWidget->setHeaderLabels(QStringList()
                                    << "Index"
                                    << "Directory Name");
    connect(ui->pushButton_removedirectory, SIGNAL(clicked()),
            this, SLOT(OnDeleteIt()));

    // populate list with nodes
    load_interface("VirtualConcierge/nodes.pvc");

    // clear the directory list
    this->directories.clear();
    this->directorylist.clear();
    this->display.clear();

    // load the directories for working temp directory
    load_directories("VirtualConcierge/directories.dir");
}

UserInterfaceCreator::~UserInterfaceCreator() {
    delete ui;
}

void UserInterfaceCreator::on_pushButton_adddirectory_clicked() {
    AddAfterCurrentIndex();
}

void UserInterfaceCreator::addTreeRoot(QString name, QString description) {
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description);

    // clear the prev list
    ui->listWidget_nodes_directories->clear();

     // add the new list to the addable items
    for ( int l = 0; l < ui->treeWidget->topLevelItemCount(); l++ ) {
         QTreeWidgetItem *item_ = ui->treeWidget->topLevelItem(l);
         ui->listWidget_nodes_directories->addItem(
                     item_->text(1) +
                     "," +
                     item_->text(0));
    }

    // populate list with nodes
    load_interface("VirtualConcierge/nodes.pvc");
}

void UserInterfaceCreator::addTreeChild(QTreeWidgetItem *parent,
                  QString name, QString description) {
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description);

    // QTreeWidgetItem::addChild(QTreeWidgetItem * child)
    parent->addChild(treeItem);
}

void UserInterfaceCreator::OnDeleteIt() {
    // delete current selected item
    bool remove = false;
    int removed = ui->treeWidget->currentIndex().row();
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    // leave when to pointer does not exist
    if ( !item) return;

    if ( ui->treeWidget->topLevelItemCount() > removed ) {
        if ( ui->treeWidget->topLevelItem(removed)->isSelected() ) {
            ui->treeWidget->takeTopLevelItem(removed);
            remove = true;
        } else {delete item;}
    } else {delete item;}
    if ( remove ) {
        // update the other items
        for ( int l = 0; l < ui->treeWidget->topLevelItemCount(); l++ ) {
            QTreeWidgetItem *item_ = ui->treeWidget->topLevelItem(l);
            // get current index
            int index = item_->text(0).toInt();

            // shift go back one with indices
            (index > removed) && (remove) ?
                        item_->setText(0, QString::number(index - 1)) :
                        item_->setText(0, item_->text(0));

            // update or delete all the child items
            for ( int k = 0; k < item_->childCount(); k++ ) {
                QTreeWidgetItem *item_child = item_->child(k);
                int index_child = item_child->text(0).toInt();
                // go back one with indices
                (index_child > removed) && (remove) ?
                 item_child->setText(0, QString::number(index_child - 1)) :
                 item_child->setText(0, QString::number(index_child));
                if ( (index_child == removed) && (remove) ) {
                    delete item_child;
                    k--;
                }
            }
       }

       ui->listWidget_nodes_directories->clear();
        // add the new list to the addable items
       for ( int l = 0; l < ui->treeWidget->topLevelItemCount(); l++ ) {
            QTreeWidgetItem *item_ = ui->treeWidget->topLevelItem(l);
            ui->listWidget_nodes_directories->addItem(
                        item_->text(1) +
                        "," +
                        item_->text(0));
       }
       // populate list with nodes
       load_interface("VirtualConcierge/nodes.pvc");
    }
}

void UserInterfaceCreator::load_interface(QString filename) {
    // load the text file
    QFile textfile(filename);

    // open the text file
    textfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ascread(&textfile);
    // clear the nodes
    this->nodes.clear();
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
                    this->nodes.push_back(name+","+QString::number(index));
                }
            }
            // read next line
           line = ascread.readLine();
        }
        // close the textfile
        textfile.close();
    }
}

void UserInterfaceCreator::AddAfterCurrentIndex() {
  ui->listWidget_nodes_directories->addItem(
              "DIR:" +
              ui->lineEdit_new_directory->text() +
              "," +
              QString::number(ui->treeWidget->topLevelItemCount()));

  // add the root tree after the last toplevel item
  addTreeRoot(QString::number(ui->treeWidget->topLevelItemCount()),
              "DIR:" + ui->lineEdit_new_directory->text());
}

void UserInterfaceCreator::on_pushButton_add_child_clicked() {
    // only allow items to be added when an item is selected
    if ( ui->listWidget_nodes_directories->selectedItems().count() > 0 ) {
        QTreeWidgetItem *item = ui->treeWidget->currentItem();

        // get the selected item's index
        int selected_index = ui->treeWidget->currentIndex().row();
        bool selected_secondlevel = false;

        // exit when nothing is selected
        if ( !item) return;

        // check if a toplevel item was selected
        if ( ui->treeWidget->topLevelItem(selected_index)->isSelected() )
            selected_secondlevel = true;

        // add a child item to the top level
        if ( selected_secondlevel ) {
            QStringList ls =
            ui->listWidget_nodes_directories->currentItem()->text().split(",");
            addTreeChild(item, ls.value(1), ls.value(0));
        }
    }
}

void UserInterfaceCreator::save_to_file(QString) {
}

void UserInterfaceCreator::on_pushButton_add_display_clicked() {
    // only allow items to be added when an item is selected
    if ( ui->listWidget_nodes_directories->selectedItems().count() > 0 ) {
      QStringList ls =
      ui->listWidget_nodes_directories->currentItem()->text().split(",");
      ui->listWidget_display->addItem(ls.value(0)+","+ls.value(1));
      this->display.push_back(ls.value(0)+","+ls.value(1));
    }
}

void UserInterfaceCreator::on_pushButton_remove_display_clicked() {
    if ( ui->listWidget_display->selectedItems().count() > 0 ) {
        QListWidgetItem *item =  ui->listWidget_display->currentItem();
        if ( item->isSelected())
            delete item;
    }
}

void UserInterfaceCreator::on_pushButton_removedirectory_clicked() {
}

void UserInterfaceCreator::on_buttonBox_accepted() {
    // clear the directories
    this->directories.clear();
    this->directorylist.clear();
    this->display.clear();

    // add new data to the directories
    for ( int i = 0; i <ui->treeWidget->topLevelItemCount(); i++ ) {
        // get current item
        QTreeWidgetItem *item_ = ui->treeWidget->topLevelItem(i);
        // get current index
        int index = item_->text(0).toInt();
        this->directories.push_back(item_->text(1));
        QString node_children, dir_children;
        for ( int k = 0; k < item_->childCount(); k++ ) {
            QTreeWidgetItem *item_child = item_->child(k);
            QStringList ls = item_child->text(1).split(":");
            QString::compare(ls.value(0),
                             "DIR",
                             Qt::CaseInsensitive) != 0 ?
                             node_children += item_child->text(0) + ";" :
                             dir_children += item_child->text(0) + ";";
        }
        // remove the ";" at end of each list
        node_children.count() > 1 ?
                    node_children.remove(node_children.count()-1, 1):(0);
        dir_children.count() > 1 ?
                    dir_children.remove(dir_children.count()-1, 1):(0);
        this->directorylist.push_back(QString::number(index) +
                                      "," +
                                      node_children +
                                      "," +
                                      dir_children);
    }

    // add the display list of directories
    for ( int j = 0; j < ui->listWidget_display->count(); j++ ) {
        this->display.push_back(ui->listWidget_display->item(j)->text());
    }

    // export the new directories to working (temp) directory
    PremisesExporter::export_directories(this->directories,
                                         this->directorylist,
                                         this->display,
                                         "directories.dir");
}

void UserInterfaceCreator::load_directories(QString filename) {
    // clear the list of nodes
    ui->listWidget_nodes_directories->clear();
    ui->listWidget_display->clear();

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
                addTreeRoot(QString::number(count_top), list[1]);
                count_top++;
              } else if ( list[0] == "dl" ) {
                // get directory index
                int index = list[1].toInt();
                QTreeWidgetItem *item_ = ui->treeWidget->topLevelItem(index);

                // get all the children nodes
                QStringList chls = list[2].split(";");
                // count the children nodes
                int childcount = chls.count();
                // whenever the child node esist
                if ( childcount > 0 ) {
                    // search for the corresponding child
                    foreach(QString node, this->nodes) {
                        QStringList ls = node.split(",");
                        int numb = ls[1].toInt();
                        // add all the child nodes
                        for ( int x = 0; x < childcount; x++ ) {
                            int child_index = chls[x].toInt();
                            if ( child_index == numb ) {
                               addTreeChild(item_, ls[1], ls[0]);
                            }
                        }
                    }
                }
                // add subdirectories
                QStringList dirls = list[3].split(";");
                // count the subdirectories
                int subdircount = dirls.count();
                if ( subdircount > 0 ) {
                        for ( int y = 0; y < subdircount; y++ ) {
                            if ( dirls[y] != "" ) {
                                int dirindex = dirls[y].toInt();
                                QTreeWidgetItem *item_child =
                                ui->treeWidget->topLevelItem(dirindex);
                                addTreeChild(item_,
                                             item_child->text(0),
                                             item_child->text(1));
                            }
                        }
                }
            } else if ( list[0] == "dd" ) {
                ui->listWidget_display->addItem(list[1]+","+list[2]);
            }
            // read next line
           line = ascread.readLine();
        }
        // close the textfile
        textfile.close();
    }
}

void UserInterfaceCreator::on_pushButton_up_clicked() {
  // moves the selected index up ( index - 1 )
  bool isparent = false;
  int selected = ui->treeWidget->currentIndex().row();
  QTreeWidgetItem *item = ui->treeWidget->currentItem();
  if ( ui->treeWidget->topLevelItemCount() > selected ) {
      if ( ui->treeWidget->topLevelItem(selected)->isSelected() &&
           (selected > 0) ) {
        QTreeWidgetItem* replace = ui->treeWidget->takeTopLevelItem(selected);
        QTreeWidgetItem* moved = ui->treeWidget->topLevelItem(selected - 1);
        replace->setText(0, QString::number(selected - 1));
        moved->setText(0, QString::number(selected));
        ui->treeWidget->insertTopLevelItem(selected - 1, replace);
        ui->treeWidget->setCurrentItem(replace);
        isparent = true;
      }
  }
  if ( !isparent ) {
    if ( item && (selected > 0) ) {
      QTreeWidgetItem* parent = item->parent();
      int index = parent->indexOfChild(item);
      QTreeWidgetItem* child = parent->takeChild(index);
      parent->insertChild(index - 1, child);
      parent->setExpanded(true);
      child->setExpanded(true);
    }
    ui->treeWidget->setCurrentItem(item);
  }
}

void UserInterfaceCreator::on_pushButton_down_clicked() {
    // moves the selected index up ( index - 1 )
    bool isparent = false;
    int selected = ui->treeWidget->currentIndex().row();
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if ( selected < ui->treeWidget->topLevelItemCount() ) {
        if ( ui->treeWidget->topLevelItem(selected)->isSelected() &&
             selected < ui->treeWidget->topLevelItemCount() - 1 ) {
            QTreeWidgetItem* replace = ui->treeWidget->takeTopLevelItem(selected);
            QTreeWidgetItem* moved = ui->treeWidget->topLevelItem(selected);
            replace->setText(0, QString::number(selected + 1));
            moved->setText(0, QString::number(selected));
            ui->treeWidget->insertTopLevelItem(selected + 1, replace);
            ui->treeWidget->setCurrentItem(replace);
        }
      isparent = true;
    }

    if (!isparent) {
      if ( item && (selected < item->parent()->childCount() - 1) ) {
        QTreeWidgetItem* parent = item->parent();
        int index = parent->indexOfChild(item);
        QTreeWidgetItem* child = parent->takeChild(index);
        parent->insertChild(index + 1, child);
        parent->setExpanded(true);
        child->setExpanded(true);
      }
      ui->treeWidget->setCurrentItem(item);
    }
  }
