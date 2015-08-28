#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QtNetwork>
#include <QCryptographicHash>
#include <QNetworkSession>

class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    ~Client();
    void ConnectToHost(QString,int);
    void SendData(QString);
    void Login(QString, QString);
    void send_file(QString, QString);
    QString GetSession();
private:
    void ConfigureNetwork();
    QTcpSocket *tcpSocket;
    quint16 blockSize;
    QNetworkSession *networkSession;
    QByteArray session_;
    QString username_;
    QByteArray *data_to_send;
private slots:
    void readData();
    void sessionOpened();

signals:
    void logged_in(QByteArray, bool);
};

#endif // CLIENT_H
