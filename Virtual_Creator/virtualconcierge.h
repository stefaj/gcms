/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_VIRTUALCONCIERGE_H_
#define VIRTUAL_CREATOR_VIRTUALCONCIERGE_H_

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include "Objects/nodebutton.h"
#include "RenderStates/virtualconciergerenderstate.h"

namespace Ui {
class VirtualConcierge;
}

class VirtualConcierge : public QWidget {
    Q_OBJECT

 public:
    explicit VirtualConcierge(QWidget *parent = 0);
    ~VirtualConcierge();

 private:
    Ui::VirtualConcierge *ui;
    void create_interface();
    void load_interface(QString path_nodes, QString path_directories);
    int get_index_from_index(QVector<NodeButton* > node_list, int index);
    QVector<NodeButton *> buttons_, directories_, catagory_, temp;
    QVector<QString> directory_list_, node_list_;

 private slots:
    void get_button_value(int index, bool significant);
    void on_pushButton_send_mail_clicked();
    void show_new_interface(int selected_node);

 signals:
    void find_path(int start, int goal);
};

#endif  // VIRTUAL_CREATOR_VIRTUALCONCIERGE_H_
