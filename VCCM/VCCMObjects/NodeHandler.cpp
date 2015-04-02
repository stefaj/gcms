#include "VCCMObjects/NodeHandler.h"

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
        m_premises.value(index1)->AddLink( new QString(m_premises.value(index2)->getName()),index1);
    else
        qDebug()<< "Node can't be linked to itself";
}
