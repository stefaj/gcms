#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    logged_in_(false),
    ui(new Ui::login) {
    ui->setupUi(this);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_password->setInputMethodHints(Qt::ImhHiddenText |
                                               Qt::ImhNoPredictiveText |
                                               Qt::ImhNoAutoUppercase);
}

login::~login() {
    delete ui;
}

void login::on_pushButton_login_clicked() {
    client_logging = new Client();
    connect(client_logging, SIGNAL(logged_in(QString, bool)),
            this, SLOT(logged_in(QString, bool)));
    client_logging->Login(ui->lineEdit_username->text(),
                          ui->lineEdit_password->text());
}

void login::logged_in(QString session, bool value) {
  logged_in_ = value;
  if( value ) {
    this->close();
  }
  qDebug() << session;
}

bool login::get_logged() {
  return logged_in_;
}

void login::on_pushButton_terminate_clicked() {
    // completely exit the program
    QApplication::exit(0);
}

void login::on_pushButton_close_clicked() {
  // close the window
  this->close();
}
