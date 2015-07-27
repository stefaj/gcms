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

    // Add root node
//    addTreeRoot("0", "First");
//    addTreeRoot("1", "Second");
//    addTreeRoot("2", "third");
    // populate list with nodes
    load_interface("VirtualConcierge/nodes.pvc");
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
//    addTreeChild(treeItem, name + "A", "Child_first");
//    addTreeChild(treeItem, name + "B", "Child_second");
//    addTreeChild(treeItem->child(0), name + "B", "Child_second");
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
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    delete item;
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
        addTreeRoot(QString::number(ui->treeWidget->topLevelItemCount()),ui->lineEdit_new_directory->text());
}
