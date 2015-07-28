#include "userinterfacecreator.h"
#include "ui_userinterfacecreator.h"
#include <QDebug>

UserInterfaceCreator::UserInterfaceCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserInterfaceCreator){

    ui->setupUi(this);
    // Set the number of columns in the tree
    ui->treeWidget->setColumnCount(2);

    // Set the headers
    ui->treeWidget->setHeaderLabels(QStringList() << "Index" << "Directory Name");
    connect(ui->pushButton_removedirectory,SIGNAL(clicked()),this,SLOT(OnDeleteIt()));

    // populate list with nodes
    load_interface("VirtualConcierge/nodes.pvc");

    // clear the directory list
    m_directories.clear();
}

UserInterfaceCreator::~UserInterfaceCreator(){
    delete ui;
}

void UserInterfaceCreator::on_pushButton_adddirectory_clicked(){
    AddAfterCurrentIndex();
}

void UserInterfaceCreator::addTreeRoot(QString name, QString description){

    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description);

    // clear the prev list
    ui->listWidget_nodes_directories->clear();

     // add the new list to the addable items
    for(int l = 0;l<ui->treeWidget->topLevelItemCount();l++){
         QTreeWidgetItem *item_ = ui->treeWidget->topLevelItem(l);
         ui->listWidget_nodes_directories->addItem(item_->text(1)+","+item_->text(0));
    }

    // populate list with nodes
    load_interface("VirtualConcierge/nodes.pvc");
}

void UserInterfaceCreator::addTreeChild(QTreeWidgetItem *parent,
                  QString name, QString description){

    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description);

    // QTreeWidgetItem::addChild(QTreeWidgetItem * child)
    parent->addChild(treeItem);
}

void UserInterfaceCreator::OnDeleteIt(){
    // delete current selected item
    bool remove = false;
    int removed = ui->treeWidget->currentIndex().row();
    QTreeWidgetItem *item = ui->treeWidget->currentItem();

    // leave when to pointer does not exist
    if(!item) return;

    if(ui->treeWidget->topLevelItem(removed)->isSelected()){
        ui->treeWidget->takeTopLevelItem(removed);
        remove = true;
    }else delete item;

    // update the other items
    for(int l = 0;l<ui->treeWidget->topLevelItemCount();l++){
        QTreeWidgetItem *item_ = ui->treeWidget->topLevelItem(l);
        // get current index
        int index = item_->text(0).toInt();

        // shift go back one with indices
        (index > removed)&&(remove) ? item_->setText(0,QString::number(index-1)) : item_->setText(0,item_->text(0));

        // update or delete all the child items
        for(int k = 0; k<item_->childCount();k++){
            QTreeWidgetItem *item_child = item_->child(k);
            int index_child = item_child->text(0).toInt();
            // go back one with indices
            (index_child > removed)&&(remove)? item_child->setText(0,QString::number(index_child-1)):item_child->setText(0,QString::number(index_child));
            if((index_child==removed)&&(remove)){delete item_child; k--;}
        }
   }

   ui->listWidget_nodes_directories->clear();
    // add the new list to the addable items
   for(int l = 0;l<ui->treeWidget->topLevelItemCount();l++){
        QTreeWidgetItem *item_ = ui->treeWidget->topLevelItem(l);
        ui->listWidget_nodes_directories->addItem(item_->text(1)+","+item_->text(0));
   }
   // populate list with nodes
   load_interface("VirtualConcierge/nodes.pvc");
}

void UserInterfaceCreator::load_interface(QString filename){
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
                    ui->listWidget_nodes_directories->addItem(name+","+QString::number(index));
                }
            }
            // read next line
           line = ascread.readLine();
        }

        // close the textfile
        textfile.close();
    }
}

void UserInterfaceCreator::AddAfterCurrentIndex(){
  // qDebug()<< ui->treeWidget->selectedItems().count();

  ui->listWidget_nodes_directories->addItem("DIR:"+ui->lineEdit_new_directory->text()+","+QString::number(ui->treeWidget->topLevelItemCount()));

  addTreeRoot(QString::number(ui->treeWidget->topLevelItemCount()),"DIR:"+ui->lineEdit_new_directory->text());
}

void UserInterfaceCreator::on_pushButton_add_child_clicked(){

    // only allow items to be added when an item is selected
    if(ui->listWidget_nodes_directories->selectedItems().count()>0){
        QTreeWidgetItem *item = ui->treeWidget->currentItem();

        // get the selected item's index
        int selected_index = ui->treeWidget->currentIndex().row();
        bool selected_secondlevel = false;

        // exit when nothing is selected
        if(!item) return;

        // check if a toplevel item was selected
        if(ui->treeWidget->topLevelItem(selected_index)->isSelected())
            selected_secondlevel = true;

        // add a child item to the top level
        if(selected_secondlevel){
            QStringList ls =ui->listWidget_nodes_directories->currentItem()->text().split(",");
            addTreeChild(item,ls.value(1),ls.value(0));
        }
    }
}

void UserInterfaceCreator::save_to_file(QString){

}
