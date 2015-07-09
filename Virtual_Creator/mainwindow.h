#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_button_node_clicked();
    void on_button_link_clicked();

    void on_button_remove_clicked();

    void on_button_pavement_clicked();

private:
    Ui::MainWindow *ui;
    void EmitSignals();
signals:
    void place_node(bool); // allows a node to be placed
    void node_links(bool); // allow nodes to be linkeds
    void remove_nodes(bool); // allow nodes to be destroyed
    void place_pavement(bool);
};

#endif // MAINWINDOW_H
