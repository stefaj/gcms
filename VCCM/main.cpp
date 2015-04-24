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
#include <QDebug>
#include "VCCMUI/BackBone.h"

//This is the main function of the program, everything happens here
int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QQuickView view; // quickqt view instance
    QSurfaceFormat format;// rendering format
    format.setSamples(16);// antialiasing x4
    view.setFormat(format);// set the render format
    view.setResizeMode(QQuickView::SizeRootObjectToView); // resize the window to the quickqt window size
    qmlRegisterType<BackBone>("QMLOpenGL", 1, 0, "OpenGL"); // immplement the opengl to qml
    QObject::connect((QObject*)view.engine(), SIGNAL(quit()), &app, SLOT(quit())); // connect qml signal to qt signal
    view.setSource(QUrl("qrc:///Menu")); // load source
    view.show(); // show the qml window
    return app.exec(); // execute the application
}
