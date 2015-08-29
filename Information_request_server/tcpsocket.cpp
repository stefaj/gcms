#include "tcpsocket.h"
#include <QHostAddress>
TcpSocket::TcpSocket(QTcpSocket * socket): Socket ( socket )
{
    connect (Socket, SIGNAL (readyRead()), this, SLOT (sltReadyRead()));
    connect (Socket, SIGNAL (connected()), this, SLOT (sltConnected()));
    connect (Socket, SIGNAL (disconnected()), this, SLOT (sltDisconnect()));
}
void TcpSocket :: sltReadyRead ()
{
    emit dataReady (this);
}
void TcpSocket ::sltDisconnect ()
{
    emit disconnected(this);
}
void TcpSocket ::sltConnected ()
{
    emit connected(this);
}
QByteArray TcpSocket::readAll()
{
    return Socket->readAll();
}
void TcpSocket::flush() {
    Socket->flush();
}

void TcpSocket::write(QByteArray data)
{
    Socket->write(data);
}
QString TcpSocket::Address()
{
    return Socket->peerAddress().toString();
}
void TcpSocket::disconnectFromHost()
{
    Socket->disconnectFromHost();
}

TcpSocket::~TcpSocket(){}
