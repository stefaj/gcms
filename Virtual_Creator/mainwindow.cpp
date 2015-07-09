#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set clickable buttons
    ui->button_node->setCheckable(true);
    ui->button_link->setCheckable(true);
    ui->button_remove->setCheckable(true);
    ui->button_pavement->setCheckable(true);

    connect(this,SIGNAL(place_node(bool)),ui->openGLWidget, SLOT(allow_node(bool)));
    connect(this,SIGNAL(remove_nodes(bool)),ui->openGLWidget, SLOT(allow_remove(bool)));
    connect(this,SIGNAL(node_links(bool)),ui->openGLWidget, SLOT(allow_link(bool)));
    connect(this,SIGNAL(place_pavement(bool)),ui->openGLWidget, SLOT(allow_pavement(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::EmitSignals()
{
    emit node_links(ui->button_link->isChecked());
    emit place_node(ui->button_node->isChecked());
    emit remove_nodes(ui->button_remove->isChecked());
    emit place_pavement(ui->button_pavement->isChecked());
}

void MainWindow::on_button_node_clicked()
{
    ui->button_link->setChecked(false);
    ui->button_remove->setChecked(false);
    ui->button_pavement->setChecked(false);
    EmitSignals();

}

void MainWindow::on_button_link_clicked()
{
    ui->button_node->setChecked(false);
    ui->button_remove->setChecked(false);
    ui->button_pavement->setChecked(false);
    EmitSignals();
}

void MainWindow::on_button_remove_clicked()
{
    ui->button_node->setChecked(false);
    ui->button_link->setChecked(false);
    ui->button_pavement->setChecked(false);
    EmitSignals();

}

void MainWindow::on_button_pavement_clicked()
{
    ui->button_node->setChecked(false);
    ui->button_link->setChecked(false);
    ui->button_remove->setChecked(false);
    EmitSignals();
}
