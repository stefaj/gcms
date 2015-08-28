#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "./Network/client.h"
#include "./mainwindow.h"
namespace Ui {
class login;
}

class login : public QWidget {
  Q_OBJECT

public:
  explicit login(QWidget *parent = 0);
  ~login();
  bool get_logged();

private slots:
  void on_pushButton_login_clicked();
  void logged_in(QByteArray, bool);

  void on_pushButton_terminate_clicked();

  void on_pushButton_close_clicked();

private:
  bool logged_in_;
  QByteArray session_;
  Ui::login *ui;
  Client *client_logging;

};

#endif // LOGIN_H
