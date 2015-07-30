#include "nodebutton.h"

NodeButton::NodeButton(QWidget *parent) :QPushButton(parent),directory(false){
}

void NodeButton::setIndex(int value){
    this->index = value;
}

int NodeButton::getIndex(){
    return this->index;
}

void NodeButton::mousePressEvent(QMouseEvent * ){
    emit clicked_index(this->index, this->directory);
}

void NodeButton::setDirectory(bool directory){
    this->directory = directory;
}

bool NodeButton::isDirectory(){
    return this->directory;
}

NodeButton::~NodeButton()
{

}

