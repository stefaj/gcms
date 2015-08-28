#include "server.h"
#include <QtCore/QCoreApplication>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QtWidgets/QLabel>

Server::Server() : db(QSqlDatabase::addDatabase("QMYSQL")),
    m_host(""),
    m_dbname(""),
    m_user(""),
    m_pass("") {
    blocksize = 0;
    client_connection = new QList<TcpSocket*>();
    user_data = new QList<QByteArray*>();
    bool connected = ConnectDB("localhost", "vccms", "root", "ascent");
    qDebug() << "Connecting to database"
             << m_dbname
             << " from "
             << m_user
             << "@"
             << m_host; // display connecting status
    if(connected)
        qDebug() << "Connected to database"<<m_dbname;
    else
        qDebug() << "Could not connect to database";

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

bool Server::ConnectDB(QString Host,
                       QString DatabaseName,
                       QString Username,
                       QString Password) {
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

void Server::sessionOpened() {
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
  for ( int i = 0; i < ipAddressesList.size(); ++i ) {
      if ( ipAddressesList.at(i) != QHostAddress::LocalHost &&
          ipAddressesList.at(i).toIPv4Address() ) {
          ipAddress = ipAddressesList.at(i).toString();
          break;
      }
  }
  // if we did not find one, use IPv4 localhost
  if ( ipAddress.isEmpty() )
      ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
  qDebug()<<"The server is running on port:"<<m_tcpserver->serverPort();

}

int Server::get_tcp_index(TcpSocket * point) {
  for (int k = 0; k < client_connection->count(); k++ ) {
      if ( client_connection->value(k) == point ) {
          return k;
      }
  }
  return -1;
}

void Server::reply() {
    client_connection->append(new TcpSocket(m_tcpserver->nextPendingConnection()));
    user_data->append(new QByteArray(""));
    connect(client_connection->value(client_connection->count()-1),
            SIGNAL(dataReady(TcpSocket*)), this, SLOT(read(TcpSocket*)));
    connect(client_connection->value(client_connection->count() - 1),
            SIGNAL(disconnected(TcpSocket*)),
            client_connection->value(client_connection->count() - 1),
            SLOT(deleteLater()));
    connect(client_connection->value(client_connection->count()-1),
            SIGNAL(disconnected(TcpSocket*)), this, SLOT(disconnected(TcpSocket*)));
    client_connection->value(client_connection->count() - 1)->
            write(QString("connection_accepted").toLocal8Bit());
}

void Server::process(QByteArray user_data, TcpSocket* socket) {
    QList<QByteArray> data = user_data.split(',');
    QByteArray file_data = user_data;
    QString requested_type = QString::fromUtf8(data.value(0).constData());
    if ( (data.count() > 2) && requested_type.compare("log") == 0) {
    login(data.value(1), data.value(2), socket);
    }
    if( (data.count() > 2) && requested_type.compare("session_file") == 0 ) {

        int remove_len = data.value(0).count() +
                data.value(1).count() +
                data.value(2).count() + 3;
        file_data.remove(0, remove_len);
        QImage image;                 // Construct a new QImage
        image.loadFromData(file_data); // Load the image from the receive buffer
        if ( image.isNull() ) {
            QFile file("asas.txt");
            if (!file.open(QIODevice::WriteOnly))
              return;
            QTextStream out(&file);
            out << file_data;
            file.close();
        } else
        image.save("abcasd.png");

    }
}

void Server::read(TcpSocket* sock) {
  QByteArray array = sock->readAll();
  int index = get_tcp_index(sock);
  if(user_data->count() > 0 && user_data->count() > index ) {
    user_data->value(index)->append(array);

    int begin_index = user_data->value(index)->indexOf("<data>");
    int end_index = user_data->value(index)->indexOf("</data>");
    while ( begin_index > -1 && end_index > -1 && begin_index < end_index ) {
      // process data here
      QByteArray data_needed = user_data->value(index)->mid(begin_index + 6,end_index - begin_index - 6 );
      process(data_needed, sock);
      user_data->value(index)->remove(begin_index, end_index - begin_index + 7);
      begin_index = user_data->value(index)->indexOf("<data>");
      end_index = user_data->value(index)->indexOf("</data>");
    }
  }
}

void Server::disconnected(TcpSocket* sock) {
    qDebug() << sock->Address() << " disconnected";
}

bool Server::login(QByteArray username,
                   QByteArray password,
                   TcpSocket* sock) {
    QString query_ = QString("SELECT login, password FROM logon WHERE (login = \"%1\")").arg(QString::fromUtf8(username.constData()));
    QSqlQuery query(query_);
    query.exec();
    bool requested_login = false;
    QByteArray sessiongen = generateSessionID(username);
    QString userdata="";
    while (query.next()) {
        QString name = query.value(0).toString();
        QString pass = query.value(1).toString();
        qDebug() << name <<" requested to logon server.";
        if ( QString::compare(pass, password, Qt::CaseInsensitive) == 0)
            requested_login=true;
        else
            requested_login=false;
    }
    if(requested_login)
    {
        QString _stat = QString("UPDATE logon SET session = \"%1\" WHERE (login = \"%2\")")
                .arg(QString::fromUtf8(sessiongen.constData()))
                .arg(QString::fromUtf8(username.constData()));
        QSqlQuery stat(_stat);
        stat.exec();
        userdata = QString("logged,true,%1").arg(QString::fromUtf8(sessiongen.constData()));
        qDebug() << username << " logged on to server.";
    } else {
        userdata = "logged,false,invalid";
        qDebug() << username << " failed to logon.";
    }

    sock->write(userdata.toLocal8Bit());
    return requested_login;
}

QByteArray Server::generateSessionID(QByteArray username) {
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
    QByteArray sessionvalue = username.constData();
    sessionvalue.append(QString::number(timestamp));
    QByteArray session = QCryptographicHash::hash(sessionvalue,
                                                  QCryptographicHash::Sha1);
    return session;
}

Server::~Server() {
  for(int k = 0; k < client_connection->count(); k++)
    client_connection->value(k)->disconnectFromHost();
}

