//#include <QApplication>
#include <QtCore>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>

#include <stdlib.h>
#include <QtNetwork>
#include <server.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server serve;
    return a.exec();
}
