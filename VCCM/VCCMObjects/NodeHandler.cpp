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
  /* this is the main implementation of Dijkstra's Algorithm for shortest paths from one node to another */
  /* for more details on the algorithm see the final report @ https://github.com/Baggins800/Final-Report */
  /* or contact Baggins: omega@live.co.za */

  //set nodes's colors
  m_premises.value(start)->setSourceNode();
  m_premises.value(goal)->setDestinationNode();

  // clear shortest path
  m_shortest.clear();

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

// wait while the whole que is empty ( this may be ineffective )
 while(que.count()>0)
 {
     // initialize the curren index, the index to be removed and the current min G value
  int current_index = 0;
  int remove_index = 0;
  double current_min = inf;

  // select the next value with the lowest G value
  for(int l = 0; l < que.count();l++)
  {
      if(m_premises.value(l)->getG()<current_min)
      {
          current_min=m_premises.value(l)->getG();
          current_index=que.value(l);
          remove_index = l;
      }
  }
  // remove current checked
  que.remove(remove_index);

  // mark node as checked
  checked.push_back(current_index);

  // check all the neighbor nodes
  for(int p = 0; p<m_premises.value(current_index)->countConnected();p++)
  {
       // calculate the distance between current node and the current active neigbor node
      double nodedist = m_premises.value(m_premises.value(current_index)->getConnectedIndex(p))->Position().distanceToPoint(m_premises.value(current_index)->Position());
      // test
      //qDebug()<<"distance between:"<<current_index<<" and "<<m_premises.value(current_index)->getConnectedIndex(p)<<" equals "<< nodedist;

      // replace the node's shortest current path if needed. (dist(v,u) + g(v)< g(u))
      if(nodedist +m_premises.value(current_index)->getG()< m_premises.value(m_premises.value(current_index)->getConnectedIndex(p))->getG())
      {
          // update the g value and shortest path of the neighbor
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

  // list path
  int _back_node = goal;
  m_shortest.push_back(_back_node);
  while(_back_node != start)
  {
      // backwards trace the shortest path
      _back_node = m_premises.value(_back_node)->getShortestIndex();
      m_shortest.push_back(_back_node);
  }

  // test shortest path
  //for(int k = 0; k< m_shortest.count();k++)
  //    qDebug()<<m_shortest.value(k);

}
int NodeHandler::pathcount()
{
    return m_shortest.count();
}

int NodeHandler::pathindex(int index)
{
    return m_shortest.value(index);
}
