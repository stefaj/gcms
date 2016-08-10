/* Copyright 2015 Ruan Luies */

#include "./mainwindow.h"
#include "./ui_mainwindow.h"
#include "./userinterfacecreator.h"
#include "./config_editor.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
  network_session = new QByteArray("");
  // set current page to floor plan
  ui->stackedWidget_side_add->setCurrentIndex(2);
  // connections to all the slots of the opengl widget
  connect(this, SIGNAL(place_node(bool)),
          ui->openGLWidget, SLOT(allow_node(bool)));

  connect(this, SIGNAL(remove_nodes(bool)),
          ui->openGLWidget, SLOT(allow_remove_node(bool)));
  connect(this, SIGNAL(remove_trees(bool)),
          ui->openGLWidget, SLOT(allow_remove_tree(bool)));
  connect(this, SIGNAL(node_links(bool)),
          ui->openGLWidget, SLOT(allow_link(bool)));
  connect(this, SIGNAL(place_pavement(bool)),
          ui->openGLWidget, SLOT(allow_pavement(bool)));
  connect(this, SIGNAL(place_wall(bool)),
          ui->openGLWidget, SLOT(allow_wall(bool)));
  connect(this, SIGNAL(place_door(bool)),
          ui->openGLWidget, SLOT(allow_door(bool)));
  connect(this, SIGNAL(change_rotationY(double)),
          ui->openGLWidget, SLOT(change_rotY(double)));
  connect(this, SIGNAL(invert_mouseY(bool)),
          ui->openGLWidget, SLOT(invert_mouseY(bool)));
  connect(this, SIGNAL(place_tree(bool)),
          ui->openGLWidget, SLOT(allow_tree(bool)));
  connect(this, SIGNAL(place_floor_plan(bool)),
          ui->openGLWidget, SLOT(allow_floor_plan(bool)));
  connect(this, SIGNAL(add_new_texture(QString)),
          ui->openGLWidget, SLOT(load_texture_from_file(QString)));
  connect(this, SIGNAL(set_object_scale(QVector3D)),
          ui->openGLWidget, SLOT(set_object_scale(QVector3D)));
  connect(this, SIGNAL(change_floor_selected(float)),
          ui->openGLWidget, SLOT(change_current_floor_height(float)));
  connect(this, SIGNAL(change_node_name(QString)),
          ui->openGLWidget, SLOT(set_next_node_name(QString)));
  connect(this, SIGNAL(set_node_significant(bool)),
          ui->openGLWidget, SLOT(set_next_node_significant(bool)));
  connect(this, SIGNAL(load_premises(QString)),
          ui->openGLWidget, SLOT(load_premises(QString)));
  connect(ui->actionOpen_Premises_File, SIGNAL(triggered()),
          this, SLOT(send_loaded_premises()));
  connect(ui->actionEdit_User_Interface, SIGNAL(triggered()),
          this, SLOT(load_virtual_concierge_interface()));
  connect(ui->openGLWidget, SIGNAL(opengl_initialised(bool)),
          this, SLOT(is_opengl_valid_context(bool)));
  connect(this, SIGNAL(remove_floorplan(bool)),
          ui->openGLWidget, SLOT(allow_remove_floor_plan(bool)));
  connect(this, SIGNAL(remove_link(bool)),
          ui->openGLWidget, SLOT(allow_remove_link(bool)));
  connect(this, SIGNAL(edit_floorplan(bool)),
          ui->openGLWidget, SLOT(allow_edit_floor(bool)));
  connect(this, SIGNAL(edit_node(bool)),
          ui->openGLWidget, SLOT(allow_edit_node(bool)));
  connect(ui->openGLWidget, SIGNAL(send_edit_node(QString, QVector2D, bool, bool, bool, bool, bool)),
          this, SLOT(edit_node_settings(QString, QVector2D, bool, bool, bool, bool, bool)));
  connect(this, SIGNAL(edit_node_position(QVector2D)),
          ui->openGLWidget, SLOT(edit_node_position(QVector2D)));
  connect(ui->openGLWidget, SIGNAL(send_edit_floorplan(QVector2D,float,QVector2D)),
          this, SLOT(receive_edit_floorplan(QVector2D, float, QVector2D)));
  connect(this, SIGNAL(edit_floorplan_position(QVector2D)),
          ui->openGLWidget, SLOT(edit_floorplan_position(QVector2D)));
  connect(this, SIGNAL(notify_session(QByteArray)),
          ui->openGLWidget, SLOT(receive_session(QByteArray)));
  connect(ui->openGLWidget, SIGNAL(debug_results(QString)),
          this, SLOT(error_message(QString)));
  connect(ui->actionDirectory_Wizard, SIGNAL(triggered()),
          ui->pushButton_wizard, SIGNAL(clicked()));
  connect(this, SIGNAL(edit_node_access(bool, bool, bool, bool)),
          ui->openGLWidget, SLOT(edit_node_access(bool, bool, bool, bool)));
  connect(this->ui->actionEdit_Virtual_Concierge_Config, SIGNAL(triggered()),
          this, SLOT(open_config_editor()));
  connect(this->ui->actionNew, SIGNAL(triggered()),
          this, SLOT(new_premises()));
  connect(this, SIGNAL(clear_premises()),
          ui->openGLWidget, SLOT(clear_premises()));
  connect(ui->actionSave_Premises, SIGNAL(triggered()),
          this, SLOT(save_premises()));
  connect(ui->actionSet_Virtual_Concierge_Background, SIGNAL(triggered()),
          this, SLOT(create_background()));
}

void MainWindow::create_background() {
  QString file_name = QFileDialog::getOpenFileName(this,
                                                   tr("Open Image"),
                                                   "/home/image_file",
                                                   tr("Image Files (*.png *.jpg *.bmp)"));
  if ( PremisesExporter::fileExists(file_name) ) {
    QImage img(file_name);
    img.save("VirtualConcierge/background.png");
  }
}

void MainWindow::open_config_editor() {
    Config_Editor *editor = new Config_Editor();
    connect(editor, SIGNAL(accepted()),
            ui->openGLWidget, SLOT(receive_config()));
    editor->show();
}

void MainWindow::send_config() {
    //emit send_config_data();
}

MainWindow::~MainWindow() {delete ui;}

void MainWindow::edit_node_settings(QString name,
                                    QVector2D position,
                                    bool isbutton,
                                    bool walk,
                                    bool wheelchair,
                                    bool bicycle,
                                    bool vehicle) {
  ui->checkbox_significant->setChecked(isbutton);
  ui->lineEdit_node_name->setText(name);
  ui->doubleSpinBox_node_x->setValue(position.x());
  ui->doubleSpinBox_node_y->setValue(position.y());
}

void MainWindow::is_opengl_valid_context(bool is_valid_context) {
  opengl_initialised = is_valid_context;
  if ( opengl_initialised ) {
    // load temporary stored environment
    QString temp_directory = "VirtualConcierge/environment.env";
    if ( PremisesExporter::fileExists(temp_directory) ) {
      emit load_premises(temp_directory);
    }
  }
}

void MainWindow::EmitSignals() {
}

void MainWindow::error_message(QString error) {
    // show error message
    ui->textBrowser->append(error);
}

void MainWindow::drop_down_emit() {
    emit place_door(false);
    emit place_pavement(false);
    emit place_tree(false);
    emit place_wall(false);
 if ( QString::compare(ui->comboBox_basic_adds->currentText(),
                       "Floor Plan",
                       Qt::CaseInsensitive) == 0 ) {
    emit place_floor_plan(ui->button_add_basic->isChecked());
    emit remove_floorplan(ui->button_remove_basic->isChecked());
    emit place_node(false);
    emit remove_nodes(false);
    emit node_links(false);
    emit remove_link(false);
    emit edit_node(false);
    emit edit_floorplan(ui->button_edit_basic->isChecked());
    if ( ui->button_remove_basic->isChecked() )
      ui->stackedWidget_side_add->setCurrentIndex(2);
    if ( ui->button_add_basic->isChecked() ||
         ui->button_edit_basic->isChecked() )
      ui->stackedWidget_side_add->setCurrentIndex(1);
    // emit new scale for the floor plan
    emit set_object_scale(QVector3D(
                              ui->doubleSpinBox_floor_plan_width->value(),
                              1,
                              ui->doubleSpinBox_floor_plan_height->value()));

    if ( ui->button_add_basic->isChecked() ) {
         QString file_name = QFileDialog::getOpenFileName(this,
                                        tr("Open Image"),
                                         "/home/image_file",
                                        tr("Image Files (*.png *.jpg *.bmp)"));
      if ( PremisesExporter::fileExists(file_name) ) {
       emit add_new_texture(file_name);
      } else {
         emit add_new_texture("://Texture0");
      }
    }
    ui->button_edit_basic->setEnabled(true);
 }
 if ( QString::compare(ui->comboBox_basic_adds->currentText(),
                       "Node",
                       Qt::CaseInsensitive) == 0 ) {
     emit place_floor_plan(false);
     emit remove_floorplan(false);
     emit place_node(ui->button_add_basic->isChecked());
     emit remove_nodes(ui->button_remove_basic->isChecked());
     emit node_links(false);
     emit remove_link(false);
     emit change_node_name(ui->lineEdit_node_name->text());
     emit set_node_significant(ui->checkbox_significant->isChecked());
     if ( ui->button_add_basic->isChecked() ||
          ui->button_edit_basic->isChecked() ) {
       ui->stackedWidget_side_add->setCurrentIndex(0);
     } else {
       ui->stackedWidget_side_add->setCurrentIndex(2);
     }
     emit edit_node(ui->button_edit_basic->isChecked());
     emit edit_floorplan(false);
     ui->button_edit_basic->setEnabled(true);
 }
 if ( QString::compare(ui->comboBox_basic_adds->currentText(),
                       "Link",
                       Qt::CaseInsensitive) == 0 ) {
     emit place_floor_plan(false);
     emit remove_floorplan(false);
     emit place_node(false);
     emit remove_nodes(false);
     emit node_links(ui->button_add_basic->isChecked());
     emit remove_link(ui->button_remove_basic->isChecked());
     ui->stackedWidget_side_add->setCurrentIndex(2);
     emit edit_node(false);
     emit edit_floorplan(false);
     ui->button_edit_basic->setEnabled(false);
     ui->button_edit_basic->setChecked(false);
 }
}

void MainWindow::send_loaded_premises() {
  QString file_name = QFileDialog::getOpenFileName(this,
                                     tr("Open Environment File"),
                                     "/home/environment",
                                     tr("Environment Files (*.env)"));
  if ( PremisesExporter::fileExists(file_name) ) {
      emit load_premises(file_name);
    }
}

void MainWindow::on_spin_rotationY_valueChanged(double arg1) {
  change_rotationY(arg1);
}

void MainWindow::new_premises() {
    QString path = "VirtualConcierge";
    QDir dir( path );

    dir.setFilter( QDir::NoDotAndDotDot | QDir::Files );
    foreach( QString dirItem, dir.entryList() )
    {
        if( dir.remove( dirItem ) )
        {
            qDebug() << "Deleted - " + path + QDir::separator() + dirItem ;
        }
        else
        {
            qDebug() << "Fail to delete - " + path+ QDir::separator() + dirItem;
        }
    }


    dir.setFilter( QDir::NoDotAndDotDot | QDir::Dirs );
    foreach( QString dirItem, dir.entryList() ) {
        QDir subDir( dir.absoluteFilePath( dirItem ) );
        if( subDir.removeRecursively() ) {
            qDebug() << "Deleted - All files under " + dirItem ;
        }
        else {
            qDebug() << "Fail to delete - Files under " + dirItem;
        }
    }
  emit clear_premises();
}

void MainWindow::on_checkBox_inversemouse_y_clicked(bool checked) {
  emit invert_mouseY(checked);
}

void MainWindow::on_button_execute_virtual_concierge_clicked() {

}

void MainWindow::on_doubleSpinBox_floor_plan_width_valueChanged(double arg1) {
  emit set_object_scale(QVector3D(
                              arg1,
                              1,
                            ui->doubleSpinBox_floor_plan_height->value()));
}

void MainWindow::on_doubleSpinBox_floor_plan_height_valueChanged(double arg1) {
  emit set_object_scale(QVector3D(
                            ui->doubleSpinBox_floor_plan_width->value(),
                            1,
                            arg1));
}

void MainWindow::on_spinBox_floor_level_valueChanged(int arg1) {
    // show whenever the ground floor is active
  if ( arg1 == 0 ) {
      ui->label_ground_floor->setVisible(true);
    } else {
      ui->label_ground_floor->setVisible(false);
    }
    // sends the current floor to the opengl window
  emit change_floor_selected(static_cast<float>(arg1));
}

void MainWindow::on_lineEdit_node_name_textChanged(const QString &arg1) {
  emit change_node_name(arg1);
}

void MainWindow::on_checkbox_significant_clicked(bool checked) {
  emit set_node_significant(checked);
}

void MainWindow::load_virtual_concierge_interface() {
    UserInterfaceCreator *v = new UserInterfaceCreator();
    connect(v, SIGNAL(accepted()),
            ui->openGLWidget, SLOT(receive_directories()));
    v->show();
}

void MainWindow::on_button_add_basic_clicked(bool /*checked*/) {
  ui->button_remove_basic->setChecked(false);
  ui->button_edit_basic->setChecked(false);
  drop_down_emit();
}

void MainWindow::on_button_remove_basic_clicked() {
  ui->button_add_basic->setChecked(false);
  ui->button_edit_basic->setChecked(false);
  drop_down_emit();
}

void MainWindow::on_comboBox_basic_adds_activated(const QString &/*&arg1*/) {
  drop_down_emit();
}

void MainWindow::on_button_edit_basic_clicked() {
  ui->button_add_basic->setChecked(false);
  ui->button_remove_basic->setChecked(false);
  drop_down_emit();
}

void MainWindow::on_doubleSpinBox_node_x_valueChanged(double arg1) {
  emit edit_node_position(QVector2D(arg1, this->ui->doubleSpinBox_node_y->value()));
}

void MainWindow::on_doubleSpinBox_node_y_valueChanged(double arg1) {
  emit edit_node_position(QVector2D(this->ui->doubleSpinBox_node_x->value(), arg1));
}

void MainWindow::on_doubleSpinBox_floor_x_valueChanged(double arg1) {
  emit edit_floorplan_position(QVector2D(arg1, ui->doubleSpinBox_floor_y->value()));
}

void MainWindow::copyPath(QString src, QString dst) {
    QDir dir(src);
    if (! dir.exists())
        return;

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = dst + QDir::separator() + d;
        dir.mkpath(dst_path);
        copyPath(src+ QDir::separator() + d, dst_path);
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
    }
}

void MainWindow::save_premises() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    copyPath("VirtualConcierge/", dir);
}

void MainWindow::on_doubleSpinBox_floor_y_valueChanged(double arg1) {
  emit edit_floorplan_position(QVector2D(ui->doubleSpinBox_floor_x->value(), arg1));
}

void MainWindow::receive_edit_floorplan(QVector2D position,
                                        float rotation,
                                        QVector2D scale) {
  ui->doubleSpinBox_floor_x->setValue(position.x());
  ui->doubleSpinBox_floor_y->setValue(position.y());
  ui->doubleSpinBox_floor_plan_height->setValue(scale.y());
  ui->doubleSpinBox_floor_plan_width->setValue(scale.x());
  ui->spin_rotationY->setValue(rotation);
}

void MainWindow::receive_session(QByteArray session, bool logged) {
  if ( logged ) {
    *network_session = session;
    emit notify_session(session);
  }
}

void MainWindow::on_pushButton_wizard_clicked() {
 Directory_Wizard *wizard = new Directory_Wizard();
 wizard->show();
}

void MainWindow::on_checkBox_wheelchair_clicked() {

}

void MainWindow::on_checkBox_feet_clicked() {

}

void MainWindow::on_checkBox_bicycle_clicked() {

}

void MainWindow::on_checkBox_vehicle_clicked() {

}
