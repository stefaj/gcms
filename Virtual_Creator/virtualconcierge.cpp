#include "virtualconcierge.h"
#include "ui_virtualconcierge.h"
#include <QDebug>
#include <QFileDialog>
#include <QStringList>
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
    //qDebug()<<value<<"\n";
    // 0 is the starting position
    if(!findvalue)
    emit find_path(0,value);
}

void VirtualConcierge::create_interface(){
//    NodeButton *button = new NodeButton(ui->widget_directory);
//    m_buttons.push_back(button);
    const int width = 150, height = 32;
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
                        button->setGeometry(1,m_buttons.count()*(button->height()+1),button->width(),button->height());
                        PremisesExporter::fileExists(filename_directories) ? button->hide() : button->show();
                        connect(button,SIGNAL(clicked_index(int,bool)), this ,SLOT(get_button_value(int,bool)));
                        m_buttons.push_back(button);
                    }

                }
                // read next line
               line = ascread.readLine();
            }

            // close the textfile
            textfile.close();
        }

        if(PremisesExporter::fileExists(filename_directories)){

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
                        count_top++;
                        NodeButton *button = new NodeButton(ui->widget_directory);
                        button->setText(name);
                        button->setIndex(index);
                        button->setDirectory(dir.count() > 1);
                        button->setGeometry(1,m_catagory.count()*(button->height()+1),button->width(),button->height());
                        connect(button,SIGNAL(clicked_index(int,bool)), this ,SLOT(get_button_value(int,bool)));
                        m_catagory.push_back(button);
                      }

                    // read next line
                   line = ascread.readLine();
                }

                // close the textfile
                textfile_directories.close();
            }
        }
}

VirtualConcierge::~VirtualConcierge(){
    delete ui;
}

void VirtualConcierge::on_pushButton_send_mail_clicked()
{

    //QString file = QFileDialog::getSaveFileName(this, "Save as...", "name", "PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg *.jpeg)");
    QImage img =ui->openGLWidget->grabFramebuffer();
    img.save("FloorPlan.jpg");
    //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    Smtp* smtp = new Smtp("virtualconcierge@yahoo.com", "sel_foon@1", "smtp.mail.yahoo.com",465, 30000);
    QStringList ls;
    ls.append("FloorPlan.jpg");
    smtp->sendMail("virtualconcierge@yahoo.com",ui->lineEdit_email->text() , "This is a subject", "This is a body",ls);

}
