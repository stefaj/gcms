#include "client.h"

Client::Client():blockSize(0),networkSession(0),m_session(""),m_username("") {
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
    ConnectToHost("127.0.0.1", 23);
    ConfigureNetwork();
}

void Client::Login(QString username, QString password) {
    QString logindetails = QString("log,%1,%2").arg(username).arg(password);
    m_username = username;
    SendData(logindetails);
}

QString Client::GetSession() {
   return m_session;
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

    if(tcpSocket->isOpen())
    qDebug()<<"connected to "<<hostaddress;
    else
        qDebug()<<"failed to connect to "<<hostaddress;

}

void Client::readData() {
   QByteArray array = tcpSocket->readAll();
   qDebug() << array;
   QList<QByteArray> data = array.split(',');
   if ( data.count() > 2 )
   {
       if((QString::compare(QString::fromLocal8Bit(data.value(0).constData()),
                            "logged",
                            Qt::CaseInsensitive)==0) &&
           (QString::compare(QString::fromLocal8Bit(data.value(1).constData()),
                             "true",
                             Qt::CaseInsensitive))==0) {
           m_session = QString::fromLocal8Bit(data.value(2).constData());
           emit logged_in(m_session, true);
       } else {
           emit logged_in("", false);
       }
       qDebug() << "current session:"
                << m_session.toUtf8().toHex();
   }
}

void Client::SendData(QString data) {
    tcpSocket->write(data.toLocal8Bit().constData());
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

