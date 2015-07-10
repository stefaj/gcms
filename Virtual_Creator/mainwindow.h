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

    void on_button_wall_clicked();

    void on_button_door_clicked();

    void on_spin_rotationY_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    void EmitSignals();
signals:
    void place_node(bool); // allows a node to be placed
    void node_links(bool); // allow nodes to be linkeds
    void remove_nodes(bool); // allow nodes to be destroyed
    void place_pavement(bool); // allow the placement of a node
    void place_wall(bool); // allows the placement of a wall
    void place_door(bool); // allows the placement of a wall
    void change_rotationY(double);
};

#endif // MAINWINDOW_H
