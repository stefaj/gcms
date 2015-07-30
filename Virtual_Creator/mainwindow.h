/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_MAINWINDOW_H_
#define VIRTUAL_CREATOR_MAINWINDOW_H_

#include <QMainWindow>
#include <QFileDialog>
#include "./virtualconcierge.h"
#include "Functions/premises_exporter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
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
    void place_node(bool placable);  // allows a node to be placed
    void node_links(bool linkable);  // allow nodes to be linkeds
    void remove_nodes(bool removable);  // allow nodes to be destroyed
    void remove_trees(bool removable);  // allow trees to be destroyed
    void place_pavement(bool placable);  // allow the placement of a node
    void place_wall(bool placable);  // allows the placement of a wall
    void place_door(bool placable);  // allows the placement of a wall
    void change_rotationY(double angle);  // changes the rotation in Y direction
    void place_tree(bool placable);  // allows the placement of a basic tree
    void invert_mouseY(bool invert_mouse);  // invert the y of the mouse in 3D
    void place_floor_plan(bool placable);  // allows a floorplan to bew placed
    // adds new usable texture to the list
    void add_new_texture(QString file_name);
    // set the current scale of the object active
    void set_object_scale(QVector3D scale);
    void change_floor_selected(float height);  // sets the current floor used
    void change_node_name(QString name);  // changes the name of the next node
    // set whether the node should be a button or not
    void set_node_significant(bool add_button);
    void load_premises(QString file_name);  // load premises from file
};

#endif  // VIRTUAL_CREATOR_MAINWINDOW_H_
