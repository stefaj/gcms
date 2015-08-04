/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_USERINTERFACECREATOR_H_
#define VIRTUAL_CREATOR_USERINTERFACECREATOR_H_

#include <QDialog>
#include <QTreeWidget>
#include <QFile>
#include <QVector>

namespace Ui {
class UserInterfaceCreator;
}

class UserInterfaceCreator : public QDialog {
    Q_OBJECT

 public:
    explicit UserInterfaceCreator(QWidget *parent = 0);
    ~UserInterfaceCreator();

 private slots:
    void on_pushButton_adddirectory_clicked();
    void OnDeleteIt();
    void AddAfterCurrentIndex();
    void on_pushButton_add_child_clicked();
    void on_pushButton_add_display_clicked();
    void on_pushButton_remove_display_clicked();
    void on_pushButton_removedirectory_clicked();
    void on_buttonBox_accepted();

    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();

private:
    Ui::UserInterfaceCreator *ui;
    void addTreeRoot(QString name, QString description);
    void addTreeChild(QTreeWidgetItem *parent,
                          QString name, QString description);
    void load_interface(QString filename);
    void load_directories(QString filename);
    void save_to_file(QString filename);
    QVector<QString> directories, directorylist, display, nodes;
};

#endif  // VIRTUAL_CREATOR_USERINTERFACECREATOR_H_
