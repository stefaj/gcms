/* Copyright 2015 Ruan Luies */
#include "./main.h"
#include "./login.h"
#include "./userinterfacecreator.h"
#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  login login_;
  login_.show();
  return a.exec();
}
