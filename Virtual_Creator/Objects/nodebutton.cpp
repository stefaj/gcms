#include "nodebutton.h"

NodeButton::NodeButton(QWidget *parent) :QPushButton(parent)
{

}

void NodeButton::setIndex(int value){
    m_index = value;
}

int NodeButton::getIndex(){
    return m_index;
}

void NodeButton::mousePressEvent(QMouseEvent * ){
    emit clicked_index(m_index);
}

NodeButton::~NodeButton()
{

}

