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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_node_clicked()
{
    if(ui->button_node->isChecked())
    emit place_node();
}

void MainWindow::on_button_link_clicked()
{
    if(ui->button_link->isChecked())
    emit node_links();
}
