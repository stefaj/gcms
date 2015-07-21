#include "virtualconcierge.h"
#include "ui_virtualconcierge.h"
#include <QDebug>

VirtualConcierge::VirtualConcierge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VirtualConcierge)
{
    ui->setupUi(this);
    load_interface("VirtualConcierge/nodes.pvc");
    connect(this,SIGNAL(find_path(int,int)), ui->openGLWidget ,SLOT(find_path(int,int)));
    create_interface();
}

void VirtualConcierge::get_button_value(int value){
    //qDebug()<<value<<"\n";
    // 0 is the starting position
    emit find_path(0,value);
}

void VirtualConcierge::create_interface(){
//    NodeButton *button = new NodeButton(ui->widget_directory);
//    m_buttons.push_back(button);
    const int width = 100, height = 32;
    int magic_number = floor( ui->widget_directory->height()/height);
    int column = 0, row = -1;
    for(int k = 0; k < m_buttons.count();k++){
        if(row>=magic_number){
            row = 0;
            column++;
        } else row++;
        m_buttons.value(k)->setGeometry(column*width,row*height,width,height);
    }
}

void VirtualConcierge::load_interface(QString filename){
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
                QTextStream(&list[5])>>name;
                QTextStream(&list[6])>>add;
                QTextStream(&list[1])>>index;
                if(add==1){
                    NodeButton *button = new NodeButton(ui->widget_directory);
                    button->setText(name);
                    button->setIndex(index);
                    button->setGeometry(m_buttons.count()*button->width(),0,button->width(),button->height());
                    connect(button,SIGNAL(clicked_index(int)), this ,SLOT(get_button_value(int)));
                    m_buttons.push_back(button);
                }

            }
            // read next line
           line = ascread.readLine();
        }

        // close the textfile
        textfile.close();
    }
}

VirtualConcierge::~VirtualConcierge(){
    delete ui;
}
