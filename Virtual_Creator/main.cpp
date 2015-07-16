#include "mainwindow.h"
#include <QApplication>
#include "Functions/premises_exporter.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QVector<VisualObject *> p;
    PremisesExporter::export_environment(p,"NULL");
    return a.exec();
}
