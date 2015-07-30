#ifndef VIRTUALCONCIERGE_H
#define VIRTUALCONCIERGE_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include "Objects/nodebutton.h"
#include "RenderStates/virtualconciergerenderstate.h"

namespace Ui {
class VirtualConcierge;
}

class VirtualConcierge : public QWidget
{
    Q_OBJECT

public:
    explicit VirtualConcierge(QWidget *parent = 0);
    ~VirtualConcierge();

private:
    Ui::VirtualConcierge *ui;
    void create_interface();
    void load_interface(QString,QString);
    int get_index_from_index(QVector<NodeButton* >,int);
    QVector<NodeButton *> buttons, directories;
    QVector<NodeButton *> catagory, temp;
    QVector<QString> directory_list,node_list;
private slots:
    void get_button_value(int, bool);
    void on_pushButton_send_mail_clicked();
    void show_new_interface(int);

signals:
    void find_path(int,int);

};

#endif // VIRTUALCONCIERGE_H
