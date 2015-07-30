/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_SMTP_SMTP_H_
#define VIRTUAL_CREATOR_SMTP_SMTP_H_

#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>

class Smtp : public QObject {
    Q_OBJECT

 public:
    Smtp(const QString &user, const QString &pass,
          const QString &host, int port = 465, int timeout = 30000);
    ~Smtp();

    void sendMail(const QString &from, const QString &to,
                   const QString &subject, const QString &body,
                   QStringList files = QStringList());

 signals:
    void status(const QString &);

 private slots:
    void stateChanged(QAbstractSocket::SocketState socketState);
    void errorReceived(QAbstractSocket::SocketError socketError);
    void disconnected();
    void connected();
    void readyRead();

 private:
    int timeout_;
    QString message_;
    QTextStream *t_;
    QSslSocket *socket_;
    QString from_;
    QString rcpt_;
    QString response_;
    QString user_;
    QString pass_;
    QString host_;
    int port_;
    enum states{Tls,
                HandShake,
                Auth,
                User,
                Pass,
                Rcpt,
                Mail,
                Data,
                Init,
                Body,
                Quit,
                Close};
    int state_;
};
#endif  // VIRTUAL_CREATOR_SMTP_SMTP_H_
