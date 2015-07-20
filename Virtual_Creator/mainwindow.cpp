#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    // hide things not needed
    ui->groupBox_node_settings->setVisible(false);
    ui->groupBox_floor_plan_settings->setVisible(false);

    // set clickable buttons
    ui->button_node->setCheckable(true);
    ui->button_link->setCheckable(true);
    ui->button_remove_node->setCheckable(true);
    ui->button_remove_tree->setCheckable(true);
    ui->button_pavement->setCheckable(true);
    ui->button_door->setCheckable(true);
    ui->button_wall->setCheckable(true);
    ui->button_tree1->setCheckable(true);
    ui->button_floor_plan->setCheckable(true);

    // connections to all the slots of the opengl widget
    connect(this, SIGNAL(place_node(bool)),ui->openGLWidget, SLOT(allow_node(bool)));
    connect(this, SIGNAL(remove_nodes(bool)),ui->openGLWidget, SLOT(allow_remove_node(bool)));
    connect(this, SIGNAL(remove_trees(bool)),ui->openGLWidget, SLOT(allow_remove_tree(bool)));
    connect(this, SIGNAL(node_links(bool)),ui->openGLWidget, SLOT(allow_link(bool)));
    connect(this, SIGNAL(place_pavement(bool)),ui->openGLWidget, SLOT(allow_pavement(bool)));
    connect(this, SIGNAL(place_wall(bool)),ui->openGLWidget, SLOT(allow_wall(bool)));
    connect(this, SIGNAL(place_door(bool)),ui->openGLWidget, SLOT(allow_door(bool)));
    connect(this, SIGNAL(change_rotationY(double)),ui->openGLWidget,SLOT(change_rotY(double)));
    connect(this, SIGNAL(invert_mouseY(bool)),ui->openGLWidget,SLOT(invert_mouseY(bool)));
    connect(this, SIGNAL(place_tree(bool)),ui->openGLWidget,SLOT(allow_tree(bool)));
    connect(this, SIGNAL(place_floor_plan(bool)),ui->openGLWidget,SLOT(allow_floor_plan(bool)));
    connect(this, SIGNAL(add_new_texture(QString)), ui->openGLWidget, SLOT(load_texture_from_file(QString)));
    connect(this, SIGNAL(set_object_scale(QVector3D)), ui->openGLWidget,SLOT(set_object_scale(QVector3D)));
    connect(this, SIGNAL(change_floor_selected(float)),ui->openGLWidget, SLOT(change_current_floor_height(float)));
}

MainWindow::~MainWindow(){delete ui;}

void MainWindow::EmitSignals(){
    emit node_links(ui->button_link->isChecked());
    emit place_node(ui->button_node->isChecked());
    emit remove_nodes(ui->button_remove_node->isChecked());
    emit place_pavement(ui->button_pavement->isChecked());
    emit place_door(ui->button_door->isChecked());
    emit place_wall(ui->button_wall->isChecked());
    emit place_tree(ui->button_tree1->isChecked());
    emit remove_trees(ui->button_remove_tree->isChecked());
    emit place_floor_plan(ui->button_floor_plan->isChecked());
    ui->groupBox_node_settings->setVisible(ui->button_node->isChecked());
    ui->groupBox_floor_plan_settings->setVisible(ui->button_floor_plan->isChecked());
}

void MainWindow::on_button_node_clicked(){
    ui->button_link->setChecked(false);
    ui->button_remove_node->setChecked(false);
    ui->button_pavement->setChecked(false);
    ui->button_door->setChecked(false);
    ui->button_wall->setChecked(false);
    ui->button_tree1->setChecked(false);
    ui->button_remove_tree->setChecked(false);
    ui->button_floor_plan->setChecked(false);

    EmitSignals();
}

void MainWindow::on_button_link_clicked(){
    ui->button_node->setChecked(false);
    ui->button_remove_node->setChecked(false);
    ui->button_pavement->setChecked(false);
    ui->button_door->setChecked(false);
    ui->button_wall->setChecked(false);
    ui->button_tree1->setChecked(false);
    ui->button_remove_tree->setChecked(false);
    ui->button_floor_plan->setChecked(false);

    EmitSignals();
}

void MainWindow::on_button_remove_node_clicked(){
    ui->button_node->setChecked(false);
    ui->button_link->setChecked(false);
    ui->button_pavement->setChecked(false);
    ui->button_door->setChecked(false);
    ui->button_wall->setChecked(false);
    ui->button_tree1->setChecked(false);
    ui->button_remove_tree->setChecked(false);
    ui->button_floor_plan->setChecked(false);

    EmitSignals();

}

void MainWindow::on_button_pavement_clicked(){
    ui->button_node->setChecked(false);
    ui->button_link->setChecked(false);
    ui->button_remove_node->setChecked(false);
    ui->button_door->setChecked(false);
    ui->button_wall->setChecked(false);
    ui->button_tree1->setChecked(false);
    ui->button_remove_tree->setChecked(false);
    ui->button_floor_plan->setChecked(false);

    EmitSignals();
}

void MainWindow::on_button_wall_clicked(){
    ui->button_node->setChecked(false);
    ui->button_link->setChecked(false);
    ui->button_remove_node->setChecked(false);
    ui->button_door->setChecked(false);
    ui->button_pavement->setChecked(false);
    ui->button_tree1->setChecked(false);
    ui->button_remove_tree->setChecked(false);
    ui->button_floor_plan->setChecked(false);

    EmitSignals();

}

void MainWindow::on_button_door_clicked(){
    ui->button_node->setChecked(false);
    ui->button_link->setChecked(false);
    ui->button_remove_node->setChecked(false);
    ui->button_pavement->setChecked(false);
    ui->button_wall->setChecked(false);
    ui->button_tree1->setChecked(false);
    ui->button_remove_tree->setChecked(false);
    ui->button_floor_plan->setChecked(false);

    EmitSignals();
}

void MainWindow::on_spin_rotationY_valueChanged(double arg1){change_rotationY(arg1);}

void MainWindow::on_checkBox_inversemouse_y_clicked(bool checked){emit invert_mouseY(checked);}

void MainWindow::on_button_tree1_clicked(){
    ui->button_node->setChecked(false);
    ui->button_link->setChecked(false);
    ui->button_remove_node->setChecked(false);
    ui->button_pavement->setChecked(false);
    ui->button_wall->setChecked(false);
    ui->button_door->setChecked(false);
    ui->button_remove_tree->setChecked(false);
    ui->button_floor_plan->setChecked(false);

    EmitSignals();
}

void MainWindow::on_button_remove_tree_clicked(){
    ui->button_node->setChecked(false);
    ui->button_link->setChecked(false);
    ui->button_remove_node->setChecked(false);
    ui->button_pavement->setChecked(false);
    ui->button_wall->setChecked(false);
    ui->button_door->setChecked(false);
    ui->button_tree1->setChecked(false);
    ui->button_floor_plan->setChecked(false);

    EmitSignals();
}

void MainWindow::on_button_execute_virtual_concierge_clicked()
{
    VirtualConcierge *co = new VirtualConcierge();
    co->show();
}

void MainWindow::on_button_floor_plan_clicked()
{
    ui->button_node->setChecked(false);
    ui->button_link->setChecked(false);
    ui->button_remove_node->setChecked(false);
    ui->button_pavement->setChecked(false);
    ui->button_wall->setChecked(false);
    ui->button_door->setChecked(false);
    ui->button_tree1->setChecked(false);
    ui->button_remove_tree->setChecked(false);
    EmitSignals();

    // emit new scale for the floor plan
    emit set_object_scale(QVector3D(ui->doubleSpinBox_floor_plan_width->value(),1,ui->doubleSpinBox_floor_plan_height->value()));

    if(ui->button_floor_plan->isChecked()){
        QString file_name = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home/image_file", tr("Image Files (*.png *.jpg *.bmp)"));
        if(PremisesExporter::fileExists(file_name)){
            emit add_new_texture(file_name);
        } else{
            emit add_new_texture("://Texture0");
        }
    }

}

void MainWindow::on_doubleSpinBox_floor_plan_width_valueChanged(double arg1)
{
    emit set_object_scale(QVector3D(arg1,1,ui->doubleSpinBox_floor_plan_height->value()));
}

void MainWindow::on_doubleSpinBox_floor_plan_height_valueChanged(double arg1)
{
    emit set_object_scale(QVector3D(ui->doubleSpinBox_floor_plan_width->value(),1,arg1));
}

void MainWindow::on_spinBox_floor_level_valueChanged(int arg1)
{
    // show whenever the ground floor is active
    if(arg1==0){
        ui->label_ground_floor->setVisible(true);
    } else {
        ui->label_ground_floor->setVisible(false);
    }
    // sends the current floor to the opengl window
    emit change_floor_selected((float)arg1);
}
