/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_MAINWINDOW_H_
#define VIRTUAL_CREATOR_MAINWINDOW_H_

#include <QMainWindow>
#include <QFileDialog>
#include "./virtualconcierge.h"
#include "Functions/premises_exporter.h"
#include "./directory_wizard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

 private slots:

    void on_spin_rotationY_valueChanged(double arg1);
    void on_checkBox_inversemouse_y_clicked(bool checked);
    void on_button_execute_virtual_concierge_clicked();
    void on_doubleSpinBox_floor_plan_width_valueChanged(double arg1);
    void on_doubleSpinBox_floor_plan_height_valueChanged(double arg1);
    void on_spinBox_floor_level_valueChanged(int arg1);
    void on_lineEdit_node_name_textChanged(const QString &arg1);
    void on_checkbox_significant_clicked(bool checked);
    void send_loaded_premises();
    void load_virtual_concierge_interface();
    void is_opengl_valid_context(bool);
    void on_button_add_basic_clicked(bool checked);
    void on_button_remove_basic_clicked();
    void on_comboBox_basic_adds_activated(const QString &arg1);
    void on_button_edit_basic_clicked();
    void edit_node_settings(QString name,
                            QVector2D position,
                            bool isbutton,
                            bool walk,
                            bool wheelchair,
                            bool bicycle,
                            bool vehicle);
    void receive_edit_floorplan(QVector2D position,
                             float rotation,
                             QVector2D scale);
    void on_doubleSpinBox_node_x_valueChanged(double arg1);
    void on_doubleSpinBox_node_y_valueChanged(double arg1);
    void on_doubleSpinBox_floor_x_valueChanged(double arg1);
    void on_doubleSpinBox_floor_y_valueChanged(double arg1);
    void receive_session(QByteArray session, bool logged);
    void error_message(QString error);
    void on_pushButton_wizard_clicked();
    void on_checkBox_wheelchair_clicked();
    void on_checkBox_feet_clicked();
    void on_checkBox_bicycle_clicked();
    void on_checkBox_vehicle_clicked();
    void open_config_editor();
    void send_config();

private:
    Ui::MainWindow *ui;
    void EmitSignals();
    void drop_down_emit();
    bool opengl_initialised;
    QByteArray *network_session;

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
    // allows the floorplans to be removed
    void remove_floorplan(bool removable);
    void remove_link(bool removeable); // allows links to be broken
    void edit_floorplan(bool edit); // allows links to be edited
    void edit_node(bool edit); // allows nodes to be edited
    void edit_node_position(QVector2D); // sends the new coordinates to the renderstate
    void edit_floorplan_position(QVector2D); // sends the edited positions for the floor back
    void notify_session(QByteArray); // sends the current session to renderstate
    // sends the node's new values
    void edit_node_access(bool walk, bool wheelchair, bool vehicle, bool bicycle);
    void send_config_data(QString data);
};

#endif  // VIRTUAL_CREATOR_MAINWINDOW_H_
