/* Copyright 2015 Ruan Luies */

#include <QNetworkProxy>
#include "SMTP/smtp.h"

Smtp::Smtp(const QString &user,
           const QString &pass,
           const QString &host,
           int port,
           int timeout) {
    this->socket_ = new QSslSocket(this);
    QNetworkProxy proxy;

    proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName("cache10.p.nwu.ac.za");
    proxy.setPort(80);
    proxy.setUser("23511354");
    proxy.setPassword("lolipop");

    this->socket_->setProxy(proxy);
    connect(this->socket_, SIGNAL(readyRead()),
            this, SLOT(readyRead()));
    connect(this->socket_, SIGNAL(connected()),
            this, SLOT(connected() ) );
    connect(this->socket_, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(this->socket_, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(this->socket_, SIGNAL(disconnected()),
            this, SLOT(disconnected()));

    this->user_ = user;
    this->pass_ = pass;

    this->host_ = host;
    this->port_ = port;
    this->timeout_ = timeout;
}

void Smtp::sendMail(const QString &from,
                    const QString &to,
                    const QString &subject,
                    const QString &body,
                    QStringList files) {
    message_ = "To: " + to + "\n";
    message_.append("From: " + from + "\n");
    message_.append("Subject: " + subject + "\n");
    // Let's intitiate multipart MIME with cutting boundary "frontier"
    message_.append("MIME-Version: 1.0\n");
    message_.append("Content-Type: multipart/mixed; boundary=frontier\n\n");
    message_.append("--frontier\n");
    // Uncomment this for HTML formating, coment the line below
    // message.append( "Content-Type: text/html\n\n" );
    message_.append("Content-Type: text/plain\n\n");
    message_.append(body);
    message_.append("\n\n");

    if ( !files.isEmpty() ) {
        qDebug() << "Files to be sent: " << files.size();
        foreach(QString filePath, files) {
            QFile file(filePath);
            if ( file.exists() ) {
                if ( !file.open(QIODevice::ReadOnly) ) {
                    qDebug("Couldn't open the file");
                    QMessageBox::warning(
                                0,
                                tr("Qt Simple SMTP client"),
                                tr("Couldn't open the file\n\n"));
                        return;
                }
                QByteArray bytes = file.readAll();
                message_.append("--frontier\n");
                message_.append(
                            "Content-Type: "
                            "application/octet-stream\nContent-Disposition: "
                            "attachment; filename="
                            + QFileInfo(file.fileName()).fileName() +
                            ";\nContent-Transfer-Encoding: base64\n\n");
                message_.append(bytes.toBase64());
                message_.append("\n");
            }
        }
    } else {
        qDebug() << "No attachments found";
    }
    message_.append("--frontier--\n");

    message_.replace(QString::fromLatin1("\n"),
                    QString::fromLatin1("\r\n"));
    message_.replace(QString::fromLatin1("\r\n.\r\n"),
                    QString::fromLatin1("\r\n..\r\n"));
    this->from_ = from;
    this->rcpt_ = to;
    this->state_ = Init;
    // "smtp.yahoo.mail.com" and 465 for gmail TLS
    this->socket_->connectToHostEncrypted(this->host_, this->port_);
    if ( !this->socket_->waitForConnected(this->timeout_) ) {
         qDebug() << this->socket_->errorString();
     }
    this->t_ = new QTextStream( this->socket_ );
}

Smtp::~Smtp() {
    delete this->t_;
    delete this->socket_;
}

void Smtp::stateChanged(QAbstractSocket::SocketState socketState) {
    qDebug() <<"stateChanged " << socketState;
}

void Smtp::errorReceived(QAbstractSocket::SocketError socketError) {
    qDebug() << "error " <<socketError;
}

void Smtp::disconnected() {
    qDebug() <<"disconneted";
    qDebug() << "error "  << this->socket_->errorString();
}

void Smtp::connected() {
    qDebug() << "Connected ";
}

void Smtp::readyRead() {
     qDebug() <<"readyRead";
    // SMTP is line-oriented

    QString responseLine;
    while ( (this->socket_->canReadLine()) && (responseLine[3] != ' ') ) {
        responseLine = this->socket_->readLine();
        this->response_ += responseLine;
    }
    responseLine.truncate(3);
    qDebug() << "Server response code:" <<  responseLine;
    qDebug() << "Server response: " << this->response_;
    if ( this->state_ == Init && responseLine == "220" ) {
        // banner was okay, let's go on
        *(this->t_) << "EHLO localhost" <<"\r\n";
        this->t_->flush();
        this->state_ = HandShake;
    } else if ( this->state_ == HandShake && responseLine == "250" ) {
        this->socket_->startClientEncryption();
        if ( !this->socket_->waitForEncrypted(this->timeout_) ) {
            qDebug() << this->socket_->errorString();
            this->state_ = Close;
        }
        // Send EHLO once again but now encrypted
        *(this->t_) << "EHLO localhost" << "\r\n";
        this->t_->flush();
        this->state_ = Auth;
    } else if ( this->state_ == Auth && responseLine == "250" ) {
        // Trying AUTH
        qDebug() << "Auth";
        *(this->t_) << "AUTH LOGIN" << "\r\n";
        this->t_->flush();
        this->state_ = User;
    } else if ( this->state_ == User && responseLine == "334" ) {
        // Trying User
        qDebug() << "Username";
        // GMAIL is using XOAUTH2 protocol,
        // which basically means that password and
        // username has to be sent in base64 coding
        // https://developers.google.com/gmail/xoauth2_protocol
        *(this->t_) << QByteArray().append(this->user_).toBase64()  << "\r\n";
        this->t_->flush();
        this->state_ = Pass;
    } else if ( this->state_ == Pass && responseLine == "334" ) {
        // Trying pass
        qDebug() << "Pass";
        *(this->t_) << QByteArray().append(this->pass_).toBase64() << "\r\n";
        this->t_->flush();
        this->state_ = Mail;
    } else if ( this->state_ == Mail && responseLine == "235" ) {
        qDebug() << "MAIL FROM:<" << this->from_ << ">";
        *(this->t_) << "MAIL FROM:<" << this->from_ << ">\r\n";
        this->t_->flush();
        this->state_ = Rcpt;
    } else if ( this->state_ == Rcpt && responseLine == "250" ) {
        *(this->t_) << "RCPT TO:<" << this->rcpt_ << ">\r\n";
        this->t_->flush();
        this->state_ = Data;
    } else if ( this->state_ == Data && responseLine == "250" ) {
        *(this->t_) << "DATA\r\n";
        this->t_->flush();
        this->state_ = Body;
    } else if ( this->state_ == Body && responseLine == "354" ) {
        *(this->t_) << this->message_ << "\r\n.\r\n";
        this->t_->flush();
        this->state_ = Quit;
    } else if ( this->state_ == Quit && responseLine == "250" ) {
        *(this->t_) << "QUIT\r\n";
        this->t_->flush();
        // here, we just close.
        this->state_ = Close;
        emit status(tr("Message sent"));
    } else if ( this->state_ == Close ) {
        deleteLater();
        return;
    } else {  // something broke.
        QMessageBox::warning(
                    0,
                    tr("Qt Simple SMTP client"),
                    tr("Unexpected reply from SMTP server:\n\n") +
                    this->response_);
        this->state_ = Close;
        emit status(tr("Failed to send message"));
    }
    this->response_ = "";
}
