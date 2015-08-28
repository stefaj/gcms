/* Copyright 2015 Ruan Luies */
#include "./main.h"
#include "./login.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    login login_;
    login_.setWindowFlags(Qt::WindowStaysOnTopHint);
    login_.show();
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
