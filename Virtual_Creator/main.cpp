/* Copyright 2015 Ruan Luies */
#include "./main.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
