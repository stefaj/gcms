/** *********************************************************************** **/
/** *********************************************************************** **/
/**     Created by:     Ruan (Baggins) Luies 23511354                       **/
/**     email:          23511354@nwu.ac.za                                  **/
/**     Project name:   Virtual Concierge Creator And Management System     **/
/**     File Name:      Node.cpp                                            **/
/**     From Date:      2015/02/24                                          **/
/**     To Date:        2015/10/01                                          **/
/** **********************************************************************  **/
/** *********************************************************************** **/

#include "node.h"
#include <QVector2D>
#include <QVector3D>
#include <QString>

Node::Node()
{
    m_position = new QVector3D(0,0,0);
    m_name = new QString();
    m_connected.clear();
    m_links = false;
}

Node::Node(QVector3D * Position)
{
    m_position = Position;
}

Node::Node(QVector3D *Position, QString *Name)
{
    m_position = Position;
    m_name = Name;
}

void Node::AddLink(QString *Name)
{
    m_connected.push_back(Name);
    m_links = true;
}

QVector3D Node::Position()
{
    return *m_position;
}

int Node::countConnected()
{
    return m_connected.size();
}

QString Node::getLinkedName(int index)
{
    return *m_connected.value(index);
}

QString Node::getName()
{
    return *m_name;
}
