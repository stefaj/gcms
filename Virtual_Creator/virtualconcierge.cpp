#include "virtualconcierge.h"
#include "ui_virtualconcierge.h"

VirtualConcierge::VirtualConcierge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VirtualConcierge)
{
    ui->setupUi(this);
}

VirtualConcierge::~VirtualConcierge(){
    delete ui;
}
