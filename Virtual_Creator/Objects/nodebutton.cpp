#include "nodebutton.h"

NodeButton::NodeButton(QWidget *parent) :QPushButton(parent), m_directory(false)
{

}

void NodeButton::setIndex(int value){
    m_index = value;
}

int NodeButton::getIndex(){
    return m_index;
}

void NodeButton::mousePressEvent(QMouseEvent * ){
    emit clicked_index(m_index,m_directory);
}

void NodeButton::setDirectory(bool directory){
    m_directory = directory;
}

bool NodeButton::isDirectory(){
    return m_directory;
}

NodeButton::~NodeButton()
{

}

