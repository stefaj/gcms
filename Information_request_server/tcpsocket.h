#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QObject>
#include <QTcpSocket>

class TcpSocket: public QObject
{
Q_OBJECT
    QTcpSocket * Socket;
public:

    TcpSocket (QTcpSocket *);
    virtual ~TcpSocket ();
    QByteArray readAll();
    void write(QByteArray);
    QString Address();
    void disconnectFromHost();

private slots:

    void sltReadyRead ();
    void sltDisconnect ();
    void sltConnected ();

signals:
    void connected (TcpSocket * sckt);
    void disconnected (TcpSocket * sckt);
    void dataReady (TcpSocket * sckt );


};

#endif // TCPSOCKET_H
