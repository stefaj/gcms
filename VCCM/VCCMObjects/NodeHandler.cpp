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
  // initialize a checked list as empty.
  QVector<int> checked;
  //goal reached

 // set initial conditions for dijkstra's algorithm
 m_premises.value(start)->addShortest(start);
 m_premises.value(start)->setG(0.0);
 // set initial next node to starting node and minimum distance to maxmimum (inf)
 int current_node = start;
for(int l = 0; l<m_premises.count(); l++)
{
if(!checked.contains(l))
{
    current_node = l;
 while(checked.count() != m_premises.count())
 {
     double min_dist = 10000000.0;
     int next_node = current_node;
     // check all the parent nodes for the starting node
     for(int i = 0; i<m_premises.value(current_node)->countConnected();i++)
     {
         if(!checked.contains(m_premises.value(current_node)->getConnectedIndex(i))){
         float distance =m_premises.value(current_node)->Position().distanceToPoint(m_premises.value(m_premises.value(current_node)->getConnectedIndex(i))->Position());
         if(min_dist>distance)
         {
             min_dist = distance;
             next_node = m_premises.value(current_node)->getConnectedIndex(i);
         }

         m_premises.value(m_premises.value(current_node)->getConnectedIndex(i))->setG(distance);
         m_premises.value(m_premises.value(current_node)->getConnectedIndex(i))->setShortest(current_node);
         }
     }
     //add checked for starting node index
     checked.push_back(current_node);
     current_node = next_node;
     qDebug()<<"fail:"<<current_node;
 }
}
}
for(int k = 0; k < checked.count();k++)
qDebug()<<"nodes_checked:"<<k;
 for(int k = 0; k < m_premises.count();k++)
    qDebug()<<"node:"<<k<<":"<<m_premises.value(k)->getG()<<""<<m_premises.value(k)->getShortestIndex();


}
