#include "client.h"
#include <QFileDialog>

Client::Client():blockSize(0),networkSession(0),session_(""),username_("") {
    tcpSocket = new QTcpSocket(this);
    data_to_send = new QByteArray("");
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
    ConnectToHost("127.0.0.1", 23);
    ConfigureNetwork();
}

void Client::Login(QString username, QString password) {
    this->username_ = username;
    QString logindetails = QString("<data>log,%1,%2</data>").arg(username).arg(password);
    SendData(logindetails);
    // wait for bytes to be written,
    // this is not good practice, it should be removed in the future
    //tcpSocket->waitForBytesWritten(1000);
}

QString Client::GetSession() {
   return this->session_;
}

void Client::ConfigureNetwork() {
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));
        networkSession->open();
    }
}

void Client::ConnectToHost(QString hostaddress, int port) {
    QHostAddress address;
    if(address.setAddress(hostaddress))
    tcpSocket->connectToHost(hostaddress,port);

    // if(tcpSocket->isOpen())
    //  qDebug()<<"connected to "<<hostaddress;
    // else
    // qDebug()<<"failed to connect to "<<hostaddress;

}

void Client::readData() {
   QByteArray array = tcpSocket->readAll();
   QList<QByteArray> data = array.split(',');
   if ( data.count() > 2 )
   {
       if((QString::compare(QString::fromLocal8Bit(data.value(0).constData()),
                            "logged",
                            Qt::CaseInsensitive)==0) &&
           (QString::compare(QString::fromLocal8Bit(data.value(1).constData()),
                             "true",
                             Qt::CaseInsensitive))==0) {
           this->session_ = data.value(2).constData();
           emit logged_in(this->session_, true);
       } else {
           emit logged_in("", false);
       }
   }
}

void Client::SendData(QString data) {
    tcpSocket->write(data.toLocal8Bit().constData());
}

void Client::send_file(QString session, QString file_name) {
  QString session_login = QString("<data>session_file,%1,%2,").arg(session).arg(file_name);
  tcpSocket->write(session_login.toLocal8Bit());
  QByteArray ba;              // Construct a QByteArray object
  QImage image(file_name);
  if ( !image.isNull() ) {
    QBuffer buffer(&ba);        // Construct a QBuffer object using the QbyteArray
    image.save(&buffer, "PNG"); // Save the QImage data into the QBuffer
  } else {
    QFile file(file_name/*QFileDialog::getOpenFileName(NULL, tr("Upload a file"))*/);
    file.open(QIODevice::ReadOnly);
    ba = file.readAll();
    file.close();
  }
  qDebug() << session_login;
  tcpSocket->write(ba);
  QString end = "</data>";
  tcpSocket->write(end.toLocal8Bit());
}

void Client::sessionOpened() {
    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();
    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
}

Client::~Client(){

}

