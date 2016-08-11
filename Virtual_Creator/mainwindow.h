/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_MAINWINDOW_H_
#define VIRTUAL_CREATOR_MAINWINDOW_H_

#include <QMainWindow>
#include <QFileDialog>
#include <QVector2D>
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
                            QVector2D position);

    void on_doubleSpinBox_node_x_valueChanged(double arg1);
    void on_doubleSpinBox_node_y_valueChanged(double arg1);
    void error_message(QString error);
    void open_config_editor();
    void send_config();
    void new_premises();
    void create_background();

private:
    Ui::MainWindow *ui;
    void EmitSignals();
    void drop_down_emit();
    void copyPath(QString src, QString dst);
    bool opengl_initialised;

 signals:
    void place_node(bool placable);  // allows a node to be placed
    void node_links(bool linkable);  // allow nodes to be linkeds
    void remove_nodes(bool removable);  // allow nodes to be destroyed
    void change_rotationY(double angle);  // changes the rotation in Y direction
    void place_tree(bool placable);  // allows the placement of a basic tree
    void invert_mouseY(bool invert_mouse);  // invert the y of the mouse in 3D
    void place_floor_plan(bool placable);  // allows a floorplan to bew placed

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
    void clear_premises(); // sends clear signal to renderstate

};

#endif  // VIRTUAL_CREATOR_MAINWINDOW_H_
