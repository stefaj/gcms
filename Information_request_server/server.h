#ifndef SERVER_H
#define SERVER_H
#include <QString>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QtNetwork>
#include "tcpsocket.h"
#include <QCryptographicHash>

class QTcpServer;
class QNetworkSession;
class Server : public QObject
{
    Q_OBJECT
public:
    Server();
    ~Server();
    bool ConnectDB(QString Host,QString DatabaseName,QString Username,QString Password);
private:
    QSqlDatabase db;
    QString m_host,m_dbname,m_user,m_pass;
    QTcpServer *m_tcpserver;
    QNetworkSession *m_networksession;
    QList<TcpSocket*> *client_connection;
    QList<QByteArray *> *user_data;
    int get_tcp_index(TcpSocket * point);
    int blocksize;
    bool login(QByteArray, QByteArray, TcpSocket*);
    QByteArray generateSessionID(QByteArray);
    void process(QByteArray userdata, TcpSocket* socket);

private slots:
    void sessionOpened();
    void reply();
    void read(TcpSocket*);
    void disconnected(TcpSocket*);

};

#endif // SERVER_H
