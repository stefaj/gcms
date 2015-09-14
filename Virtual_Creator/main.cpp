/* Copyright 2015 Ruan Luies */
#include "./main.h"
#include "./login.h"
#include "./userinterfacecreator.h"
#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  //login login_;
  //login_.setWindowFlags(Qt::WindowStaysOnTopHint);
  //login_.setWindowFlags(Qt::FramelessWindowHint);
  //login_.show();
  MainWindow *w = new MainWindow();
  w->showMaximized();
  //qDebug() << "pewpew";
  //UserInterfaceCreator *ui = new UserInterfaceCreator();
  //ui->show();
  return a.exec();
}
