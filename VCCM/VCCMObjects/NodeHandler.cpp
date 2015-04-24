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
  // inf
  const double inf = 10000000000.0;

  // initial empty visited
  QVector<int> checked;

  // set all distances to inf
  foreach (Node *n, m_premises) {
      n->setG(inf);
  }
  // set start G value to  0.0
  m_premises.value(start)->setG(0.0);

  // initial que contains all
  QVector<int> que;

  // fill que
 for(int k = 0; k< m_premises.count();k++)
  que.push_back(k);


 while(que.count()>0)
 {
  int current_index = 0;
  int remove_index = 0;
  double current_min = inf;
  for(int l = 0; l < que.count();l++)
  {
      if(m_premises.value(l)->getG()<current_min)
      {
          current_min=m_premises.value(l)->getG();
          current_index=que.value(l);
          remove_index = l;
      }
  }
  que.remove(remove_index);
  checked.push_back(current_index);
  for(int p = 0; p<m_premises.value(current_index)->countConnected();p++)
  {

      double nodedist = m_premises.value(m_premises.value(current_index)->getConnectedIndex(p))->Position().distanceToPoint(m_premises.value(current_index)->Position());
      qDebug()<<"distance between:"<<current_index<<" and "<<m_premises.value(current_index)->getConnectedIndex(p)<<" equals "<< nodedist;
      if(nodedist +m_premises.value(current_index)->getG()< m_premises.value(m_premises.value(current_index)->getConnectedIndex(p))->getG())
      {
          m_premises.value(m_premises.value(current_index)->getConnectedIndex(p))->setG(nodedist+m_premises.value(current_index)->getG());
          m_premises.value(m_premises.value(current_index)->getConnectedIndex(p))->setShortest(current_index);
      }
  }

 }

 // test results
 for(int k = 0; k < checked.count();k++)
 qDebug()<<"nodes_checked:"<<k;
  for(int k = 0; k < m_premises.count();k++)
     qDebug()<<"node:"<<k<<":"<<m_premises.value(k)->getG()<<""<<m_premises.value(k)->getShortestIndex();



  //temp test (checked)
  /*for(int k = 0; k< m_premises.count();k++)
      Debug()<<m_premises.value(k)->getG();*/

}
int NodeHandler::pathcount()
{
    return 0;
}

int NodeHandler::pathindex(int)
{
    return 0;
}
