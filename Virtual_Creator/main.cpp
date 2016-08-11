/* Copyright 2015 Ruan Luies */
#include "./main.h"

#include <QDebug>
#include <QDir>


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow login_;
  login_.show();

  return a.exec();
}
