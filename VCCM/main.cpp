/** *********************************************************************** **/
/** *********************************************************************** **/
/**     Created by:     Ruan (Baggins) Luies 23511354                       **/
/**     email:          23511354@nwu.ac.za                                  **/
/**     Project name:   Virtual Concierge Creator And Management System     **/
/**     File Name:      main.cpp                                            **/
/**     From Date:      2015/02/24                                          **/
/**     To Date:        2015/10/01                                          **/
/** **********************************************************************  **/
/** *********************************************************************** **/

#include <QApplication>
#include <QtQuick/QQuickView>
#include <QSqlDatabase>
#include <QDebug>
#include "VCCMUI/BackBone.h"
#include <QtSql>

//This is the main function of the program, everything happens here
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QQuickView view;
    QSurfaceFormat format;// Antialiasing
    format.setSamples(4);// Antialiasing
    view.setFormat(format);// Antialiasing
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    qmlRegisterType<BackBone>("QMLOpenGL", 1, 0, "OpenGL");
    QObject::connect((QObject*)view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    view.setSource(QUrl("qrc:///Menu"));
    view.show();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
         db.setHostName("localhost");
         db.setDatabaseName("vccms");
         db.setUserName("root");
         db.setPassword("ascent");
         bool ok = db.open();
         qDebug()<<ok;
         qDebug() << QSqlDatabase::drivers();

         if(ok)
         {
             qDebug() << "Connected!";

             QSqlQuery query;
             query.exec("SELECT name FROM student");

             while (query.next()) {
                 QString name = query.value(0).toString();
                 qDebug() << "name:" << name;
             }

         }
    return app.exec();
}
