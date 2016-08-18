/* Copyright 2015 Ruan Luies */

#include "./mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
  // set current page to floor plan
  ui->stackedWidget_side_add->setCurrentIndex(2);
  // connections to all the slots of the opengl widget
  connect(this, SIGNAL(place_node(bool)),
          ui->openGLWidget, SLOT(allow_node(bool)));
  // trigger open GEXF file
  connect(this->ui->actionGEXF, SIGNAL(triggered(bool)),
          this, SLOT(open_file(bool)));
  // send GEXF filename to RenderState to open and render
  connect(this, SIGNAL(send_open_graph(QString)),
          this->ui->openGLWidget, SLOT(load_new_graph(QString)));
  connect(this, SIGNAL(remove_nodes(bool)),
          ui->openGLWidget, SLOT(allow_remove_node(bool)));
  connect(this, SIGNAL(node_links(bool)),
          ui->openGLWidget, SLOT(allow_link(bool)));
  connect(this, SIGNAL(invert_mouseY(bool)),
          ui->openGLWidget, SLOT(invert_mouseY(bool)));
  connect(this, SIGNAL(change_floor_selected(float)),
          ui->openGLWidget, SLOT(change_current_floor_height(float)));
  connect(this, SIGNAL(change_node_name(QString)),
          ui->openGLWidget, SLOT(set_next_node_name(QString)));
  connect(this, SIGNAL(set_node_significant(bool)),
          ui->openGLWidget, SLOT(set_next_node_significant(bool)));
  connect(ui->actionEdit_User_Interface, SIGNAL(triggered()),
          this, SLOT(load_virtual_concierge_interface()));
  connect(ui->openGLWidget, SIGNAL(opengl_initialised(bool)),
          this, SLOT(is_opengl_valid_context(bool)));
  connect(this, SIGNAL(edit_node(bool)),
          ui->openGLWidget, SLOT(allow_edit_node(bool)));
  connect(ui->openGLWidget, SIGNAL(send_edit_node(QString, QVector2D)),
          this, SLOT(edit_node_settings(QString, QVector2D)));
  connect(this, SIGNAL(edit_node_position(QVector2D)),
          ui->openGLWidget, SLOT(edit_node_position(QVector2D)));
  connect(ui->openGLWidget, SIGNAL(debug_results(QString)),
          this, SLOT(error_message(QString)));
  connect(this, SIGNAL(edit_node_access(bool, bool, bool, bool)),
          ui->openGLWidget, SLOT(edit_node_access(bool, bool, bool, bool)));
  connect(this->ui->actionEdit_Virtual_Concierge_Config, SIGNAL(triggered()),
          this, SLOT(open_config_editor()));
  connect(this->ui->actionNew, SIGNAL(triggered()),
          this, SLOT(new_premises()));
  connect(this, SIGNAL(clear_premises()),
          ui->openGLWidget, SLOT(clear_premises()));
  connect(ui->actionSet_Virtual_Concierge_Background, SIGNAL(triggered()),
          this, SLOT(create_background()));
}

void MainWindow::open_file(bool triggered) {
  QString file_name = QFileDialog::getOpenFileName(this,
                                                   tr("Open Graph"),
                                                   "/home/jana",
                                                   tr("Graph Files (*.gexf)"));
  emit send_open_graph(file_name);
}

void MainWindow::create_background() {

}

void MainWindow::open_config_editor() {
}

void MainWindow::send_config() {
    //emit send_config_data();
}

MainWindow::~MainWindow() {delete ui;}

void MainWindow::edit_node_settings(QString name,
                                    QVector2D position) {
  ui->lineEdit_node_name->setText(name);
  ui->doubleSpinBox_node_x->setValue(position.x());
  ui->doubleSpinBox_node_y->setValue(position.y());
}

void MainWindow::is_opengl_valid_context(bool is_valid_context) {
  opengl_initialised = is_valid_context;

}

void MainWindow::EmitSignals() {
}

void MainWindow::error_message(QString error) {
    // show error message
    ui->textBrowser->append(error);
}

void MainWindow::drop_down_emit() {

 if ( QString::compare(ui->comboBox_basic_adds->currentText(),
                       "Floor Plan",
                       Qt::CaseInsensitive) == 0 ) {

    emit place_node(false);
    emit remove_nodes(false);
    emit node_links(false);
    emit remove_link(false);
    emit edit_node(false);
    if ( ui->button_remove_basic->isChecked() )
      ui->stackedWidget_side_add->setCurrentIndex(2);
    if ( ui->button_add_basic->isChecked() ||
         ui->button_edit_basic->isChecked() )
      ui->stackedWidget_side_add->setCurrentIndex(1);

 }
 if ( QString::compare(ui->comboBox_basic_adds->currentText(),
                       "Node",
                       Qt::CaseInsensitive) == 0 ) {

     emit place_node(ui->button_add_basic->isChecked());
     emit remove_nodes(ui->button_remove_basic->isChecked());
     emit node_links(false);
     emit remove_link(false);
     emit change_node_name(ui->lineEdit_node_name->text());
     if ( ui->button_add_basic->isChecked() ||
          ui->button_edit_basic->isChecked() ) {
       ui->stackedWidget_side_add->setCurrentIndex(0);
     } else {
       ui->stackedWidget_side_add->setCurrentIndex(2);
     }
     emit edit_node(ui->button_edit_basic->isChecked());

     ui->button_edit_basic->setEnabled(true);
 }
 if ( QString::compare(ui->comboBox_basic_adds->currentText(),
                       "Link",
                       Qt::CaseInsensitive) == 0 ) {

     emit place_node(false);
     emit remove_nodes(false);
     emit node_links(ui->button_add_basic->isChecked());
     emit remove_link(ui->button_remove_basic->isChecked());
     ui->stackedWidget_side_add->setCurrentIndex(2);
     emit edit_node(false);

     ui->button_edit_basic->setEnabled(false);
     ui->button_edit_basic->setChecked(false);
 }
}

void MainWindow::send_loaded_premises() {

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

void MainWindow::on_spinBox_floor_level_valueChanged(int arg1) {
    // show whenever the ground floor is active
    // sends the current floor to the opengl window
  emit change_floor_selected(static_cast<float>(arg1));
}

void MainWindow::on_lineEdit_node_name_textChanged(const QString &arg1) {
  emit change_node_name(arg1);
}

void MainWindow::load_virtual_concierge_interface() {

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

