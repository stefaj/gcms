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

    connect(this,SIGNAL(place_node(bool)),ui->openGLWidget, SLOT(allow_node(bool)));
    connect(this,SIGNAL(remove_nodes(bool)),ui->openGLWidget, SLOT(allow_remove(bool)));
    connect(this,SIGNAL(node_links(bool)),ui->openGLWidget, SLOT(allow_link(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_node_clicked()
{
    ui->button_link->setChecked(false);
    ui->button_remove->setChecked(false);
    emit node_links(ui->button_link->isChecked());
    emit place_node(ui->button_node->isChecked());
    emit remove_nodes(ui->button_remove->isChecked());
}

void MainWindow::on_button_link_clicked()
{
    ui->button_node->setChecked(false);
    ui->button_remove->setChecked(false);
    emit node_links(ui->button_link->isChecked());
    emit place_node(ui->button_node->isChecked());
    emit remove_nodes(ui->button_remove->isChecked());
}

void MainWindow::on_button_remove_clicked()
{
    ui->button_node->setChecked(false);
    ui->button_link->setChecked(false);
    emit node_links(ui->button_link->isChecked());
    emit place_node(ui->button_node->isChecked());
    emit remove_nodes(ui->button_remove->isChecked());

}
