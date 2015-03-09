#include "server.h"
#include <QtCore/QCoreApplication>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
Server::Server() : db(QSqlDatabase::addDatabase("QMYSQL")),m_host(""),m_dbname(""),m_user(""),m_pass("")
{
    blocksize = 0;
    m_clientconnection = new QList<TcpSocket*>();
    bool connected = ConnectDB("localhost","vccms","root","ascent");
    qDebug()<< "Connecting to database"<<m_dbname<<" from "<<m_user<<"@"<<m_host; // display connecting status
    if(connected)
        qDebug()<< "Connected to database"<<m_dbname;
    else
        qDebug()<< "Could not connect to database";

    QNetworkConfigurationManager manager;
    if (manager.capabilities() && QNetworkConfigurationManager::NetworkSessionRequired) {
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

        m_networksession = new QNetworkSession(config, this);
        connect(m_networksession, SIGNAL(opened()), this, SLOT(sessionOpened()));
         m_networksession->open();

    }
    else { sessionOpened();}

    connect(m_tcpserver, SIGNAL(newConnection()), this, SLOT(reply()));

}
bool Server::ConnectDB(QString Host,QString DatabaseName,QString Username,QString Password)
{
    /* setup variables for db */

    m_host = Host;
    m_dbname =DatabaseName;
    m_user = Username;
    m_pass = Password;

    /* This sets up the connection to the database */

    // hostname, localhost not a remote connection
    db.setHostName(Host);
    // specify the db name
    db.setDatabaseName(DatabaseName);
    //the db username usually "root" for local host
    db.setUserName(Username);
    // usually "ascent" for localhost
    db.setPassword(Password);
    // returns the state of connection, connected = true, not connected = false
    return db.open();
}
void Server::sessionOpened()
{
    // Save the used configuration
  if (m_networksession) {
      QNetworkConfiguration config = m_networksession->configuration();
      QString id;
      if (config.type() == QNetworkConfiguration::UserChoice)
          id = m_networksession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
      else
          id = config.identifier();

      QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
      settings.beginGroup(QLatin1String("QtNetwork"));
      settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
      settings.endGroup();
  }

    m_tcpserver = new QTcpServer(this);
  if (!m_tcpserver->listen(QHostAddress::Any, 23)) {
      qDebug()<<m_tcpserver->errorString();
  }
  else{qDebug()<<"Listening for reply.";}
  QString ipAddress;
  QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
  // use the first non-localhost IPv4 address
  for (int i = 0; i < ipAddressesList.size(); ++i) {
      if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
          ipAddressesList.at(i).toIPv4Address()) {
          ipAddress = ipAddressesList.at(i).toString();
          break;
      }
  }
  // if we did not find one, use IPv4 localhost
  if (ipAddress.isEmpty())
      ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
  qDebug()<<"The server is running on port:"<<m_tcpserver->serverPort();

}
void Server::reply()
{
    m_clientconnection->append(new TcpSocket(m_tcpserver->nextPendingConnection()));
    qDebug()<<m_clientconnection->value(m_clientconnection->count()-1)->Address()<<" connected";
    connect(m_clientconnection->value(m_clientconnection->count()-1), SIGNAL(dataReady(TcpSocket*)), this, SLOT(read(TcpSocket*)));
    connect(m_clientconnection->value(m_clientconnection->count()-1), SIGNAL(disconnected(TcpSocket*)),m_clientconnection->value(m_clientconnection->count()-1), SLOT(deleteLater()));
    connect(m_clientconnection->value(m_clientconnection->count()-1),SIGNAL(disconnected(TcpSocket*)),this,SLOT(disconnected(TcpSocket*)));
    m_clientconnection->value(m_clientconnection->count()-1)->write(QString("connection_accepted").toLocal8Bit());
}
void Server::read(TcpSocket* sock)
{
    QByteArray array = sock->readAll();
    QList<QByteArray> data = array.split(',');
    if((data.count()>2)&&(QString::compare(QString::fromUtf8(data.value(0).constData()),"log"),Qt::CaseInsensitive)==0)
    login(data.value(1),data.value(2),sock);
}
void Server::disconnected(TcpSocket* sock)
{
    qDebug()<<sock->Address()<<" disconnected";
}
bool Server::login(QByteArray username,QByteArray password,TcpSocket* sock)
{
    QString query_=QString("SELECT login, password FROM logon WHERE (login = \"%1\")").arg(QString::fromUtf8(username.constData()));
    QSqlQuery query(query_);
    query.exec();
    bool requested_login = false;
    QByteArray sessiongen = generateSessionID(username);
    QString userdata="";
    while (query.next()) {
        QString name = query.value(0).toString();
        QString pass = query.value(1).toString();
        qDebug() << name <<" requested to logon server.";
        if(QString::compare(pass,password,Qt::CaseInsensitive)==0)
            requested_login=true;
        else
            requested_login=false;
    }
    if(requested_login)
    {
        QString _stat=QString("UPDATE logon SET session = \"%1\" WHERE (login = \"%2\")")
                .arg(QString::fromUtf8(sessiongen.constData()))
                .arg(QString::fromUtf8(username.constData()));
        QSqlQuery stat(_stat);
        stat.exec();
        userdata = QString("logged,true,%1").arg(QString::fromUtf8(sessiongen.constData()));
        qDebug()<<username<<" logged on to server.";
    } else {userdata= "logged,false,invalid";qDebug()<<username<<" failed to logon.";}

    sock->write(userdata.toLocal8Bit());
    return requested_login;
}
QByteArray Server::generateSessionID(QByteArray username)
{
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
    QByteArray sessionvalue = username.constData();
    sessionvalue.append(QString::number(timestamp));
    QByteArray session = QCryptographicHash::hash(sessionvalue,QCryptographicHash::Sha1);
    return session;
}
Server::~Server()
{
    for(int k = 0; k < m_clientconnection->count(); k++)
   m_clientconnection->value(k)->disconnectFromHost();
}

