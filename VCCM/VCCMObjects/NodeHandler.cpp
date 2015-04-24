#include "VCCMObjects/NodeHandler.h"
#include <QVector3D>
#include <qdebug.h>

NodeHandler::NodeHandler()
{
    m_premises.clear();
}

void NodeHandler::AddNode(Node* node)
{
    m_premises.push_back(node);
}

Node NodeHandler::NodeFromIndex(unsigned int index)
{
    return *m_premises.value(index);
}

int NodeHandler::count()
{
    return m_premises.count();
}

void NodeHandler::AddNodeLink(int index,QString* Name)
{
   m_premises.value(index)->AddLink(Name,index);
}

void NodeHandler::AddNodeLinkbyIndex(int index1,int index2)
{
    if(index1!=index2)
        m_premises.value(index1)->AddLink( new QString(m_premises.value(index2)->getName()),index2);
    else
        qDebug()<< "Node can't be linked to itself";
}
void NodeHandler::CalculateShortest(int start, int goal)
{
 m_premises.value(start)->addShortest(start);
 for(int i = 0; i<m_premises.value(start)->countConnected();i++)
 {
     float distance =10.0;//m_premises.value(start)->Position().distanceToPoint(m_premises.value(m_premises.value(start)->getConnectedIndex(i))->Position());
     m_premises.value(m_premises.value(start)->getConnectedIndex(i))->setG(distance);
 }
 for(int k = 0; k < m_premises.count();k++)
     qDebug()<<"node:"<<k<<":"<<m_premises.value(start)->getG();
}
