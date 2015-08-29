#include "./Network/client.h"
#include "./Functions/premises_exporter.h"
#include <QFileDialog>

Client::Client():blockSize(0),
    networkSession(0),
    session_(""),
    username_(""),
    busy_flag(false) {
    tcpSocket = new QTcpSocket(this);
    data_to_send = new QByteArray("");
    received_data = new QByteArray("");
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
    ConnectToHost("127.0.0.1", 23);
    ConfigureNetwork();
}

bool Client::busy() {
  return busy_flag;
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
  received_data->append(array);
  int begin_index = received_data->indexOf("<data>");
  int end_index = received_data->indexOf("</data>");
  while ( begin_index > -1 && end_index > -1 && begin_index < end_index ) {
    // process data here
    QByteArray data_needed = received_data->mid(begin_index + 6,end_index - begin_index - 6 );
      busy_flag = true;
    process(data_needed);
    received_data->remove(begin_index, end_index - begin_index + 7);
    begin_index = received_data->indexOf("<data>");
    end_index = received_data->indexOf("</data>");
  }
  busy_flag = false;
}

void Client::SendData(QString data) {
    tcpSocket->write(data.toLocal8Bit().constData());
}

void Client::send_file(QByteArray session, QString file_name) {
  QString session_login = QString("<data>session_file,");//.arg(session.toHex()).arg(file_name);
  tcpSocket->write(session_login.toLocal8Bit());
  tcpSocket->write(session);
  QString session_login_part_2 = QString(",%1,").arg(file_name);
  tcpSocket->write(session_login_part_2.toLocal8Bit());
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

void Client::process(QByteArray user_data) {

  QList<QByteArray> data = user_data.split(',');
  QByteArray file_data = user_data;
  QString requested_type = QString::fromUtf8(data.value(0).constData());

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
        }
        if((QString::compare(QString::fromLocal8Bit(data.value(0).constData()),
                               "logged",
                               Qt::CaseInsensitive)==0) &&
              (QString::compare(QString::fromLocal8Bit(data.value(1).constData()),
                                "false",
                                Qt::CaseInsensitive))==0) {
            emit logged_in("", false);
        }
    }

  if( (data.count() > 2) && requested_type.compare("session_file") == 0 ) {
        int remove_len = data.value(0).count() +
                data.value(1).count() +
                data.value(2).count() + 3;
        file_data.remove(0, remove_len);
        QImage image;                 // Construct a new QImage
        image.loadFromData(file_data); // Load the image from the receive buffer
        PremisesExporter::create_director();
        QString file_path = QString::fromLocal8Bit(data.value(2));
        QStringList lista = file_path.split("/");
        QString file_name = lista.count() > 1 ? lista.value(1) : lista.value(0);
        if ( image.isNull() ) {
            QFile file("VirtualConcierge/" + file_name);
            if (!file.open(QIODevice::WriteOnly))
              return;
            QTextStream out(&file);
            out << file_data;
            file.close();
        } else
        image.save("VirtualConcierge/" + file_name, "PNG");
    }
  if( (data.count() > 2) && requested_type.compare("completed") == 0 ) {
        emit download_progress(data.value(1).toInt(),
                               data.value(2).toInt());
    }

}

Client::~Client(){

}

