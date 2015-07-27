#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "virtualconcierge.h"
#include "Functions/premises_exporter.h"
#include <QFileDialog>
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
    void on_button_pavement_clicked();
    void on_button_wall_clicked();
    void on_button_door_clicked();
    void on_spin_rotationY_valueChanged(double arg1);
    void on_checkBox_inversemouse_y_clicked(bool checked);
    void on_button_tree1_clicked();
    void on_button_remove_node_clicked();
    void on_button_remove_tree_clicked();
    void on_button_execute_virtual_concierge_clicked();
    void on_button_floor_plan_clicked();
    void on_doubleSpinBox_floor_plan_width_valueChanged(double arg1);
    void on_doubleSpinBox_floor_plan_height_valueChanged(double arg1);
    void on_spinBox_floor_level_valueChanged(int arg1);
    void on_lineEdit_node_name_textChanged(const QString &arg1);
    void on_checkbox_significant_clicked(bool checked);
    void send_loaded_premises();
    void load_virtual_concierge_interface();
private:
    Ui::MainWindow *ui;
    void EmitSignals();
signals:
    void place_node(bool); // allows a node to be placed
    void node_links(bool); // allow nodes to be linkeds
    void remove_nodes(bool); // allow nodes to be destroyed
    void remove_trees(bool); // allow trees to be destroyed
    void place_pavement(bool); // allow the placement of a node
    void place_wall(bool); // allows the placement of a wall
    void place_door(bool); // allows the placement of a wall
    void change_rotationY(double); // changes the rotation in Y direction
    void place_tree(bool); // allows the placement of a basic tree
    void invert_mouseY(bool); // invert the y of the mouse in 3D
    void place_floor_plan(bool); // allows a floorplan to bew placed
    void add_new_texture(QString);// adds new usable texture to the list
    void set_object_scale(QVector3D); // set the current scale of the object active
    void change_floor_selected(float); // sets the current floor used
    void change_node_name(QString); // changes the name of the next node
    void set_node_significant(bool); // set whether the node should be a button or not
    void load_premises(QString);// load premises from file
};

#endif // MAINWINDOW_H
