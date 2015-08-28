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
    void Login(QString,QString);
    QString GetSession();
private:
    void ConfigureNetwork();
    QTcpSocket *tcpSocket;
    quint16 blockSize;
    QNetworkSession *networkSession;
    QString m_session,m_username;

private slots:
    void readData();
    void sessionOpened();

signals:
    void logged_in(QString, bool);
};

#endif // CLIENT_H
