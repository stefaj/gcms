#ifndef USERINTERFACECREATOR_H
#define USERINTERFACECREATOR_H

#include <QDialog>
#include <QTreeWidget>
#include <QFile>

namespace Ui {
class UserInterfaceCreator;
}

class UserInterfaceCreator : public QDialog
{
    Q_OBJECT

public:
    explicit UserInterfaceCreator(QWidget *parent = 0);
    ~UserInterfaceCreator();

private slots:
    void on_pushButton_adddirectory_clicked();
    void OnDeleteIt();
    void AddAfterCurrentIndex();

    void on_pushButton_add_child_clicked();

private:
    Ui::UserInterfaceCreator *ui;
    void addTreeRoot(QString name, QString description);
    void addTreeChild(QTreeWidgetItem *parent,
                          QString name, QString description);
    void load_interface(QString filename);
};

#endif // USERINTERFACECREATOR_H
