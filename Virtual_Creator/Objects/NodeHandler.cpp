/* Copyright 2015 Ruan Luies */

#include "Objects/NodeHandler.h"
#include <QVector3D>
#include <qdebug.h>
#include <QFile>
#include <QTextStream>

NodeHandler::NodeHandler() {
    this->premises.clear();
}

QString NodeHandler::DisplayError() {
  QString error_list = "";
  for ( int k = 0; k < premises.count(); k++ ) {
    if ( this->premises.value(k)->getSignificant() ) {
      int error = CalculateShortest(0, k, true, true, true, true);
      if ( error > -1 && error < premises.count() ) {
        error_list.append( "Loop/Inaccessiblity Warning for node: '" +
             premises.value(error)->getName() +
            "', Index:" + QString::number(error) + "\n");
        }
      }
  }
  return error_list;
}

QVector<int> NodeHandler::error_nodes_indices() {
    // list of all the error indices
    QVector<int> list_of_error_nodes;
    list_of_error_nodes.clear();
    for ( int k = 0; k < premises.count(); k++ ) {
        if ( this->premises.value(k)->getSignificant() ) {
        int error = CalculateShortest(0, k, true, true, true, true);
        if ( error > -1 )
        list_of_error_nodes.push_back(error);
        }
    }
    return list_of_error_nodes;
}

void NodeHandler::AddNodes(QVector<Node*> nodes) {
    this->premises.clear();
    for( int l = 0; l < nodes.count(); l++ ) {
    Node * node = new Node();
    *node = *nodes.value(l);
    this->premises.push_back(node);
  }

}

void NodeHandler::AddNode(Node* node) {
    this->premises.push_back(node);
}

Node NodeHandler::NodeFromIndex(unsigned int index) {
    return *this->premises.value(index);
}

int NodeHandler::count() {
    return this->premises.count();
}

void NodeHandler::AddNodeLink(int index, QString* Name) {
  this->premises.value(index)->AddLink(Name, index);
}

void NodeHandler::AddNodeLinkbyIndex(int index1, int index2) {
    if ( index1 != index2 )
        this->
        premises.value(index1)->
        AddLink( new QString(this->premises.value(index2)->getName()),
                             index2);
    else
        qDebug()<< "Node can't be linked to itself";
}

int NodeHandler::CalculateShortest(int start, int goal, bool walk, bool wheelchair, bool vehicle, bool bicycle) {
  /* this is the main implementation of Dijkstra's Algorithm
   for shortest paths from one node to another
   for more details on the algorithm see the final report
   @ https://github.com/Baggins800/Final-Report
   or contact Baggins: omega@live.co.za */

  // set nodes's colors
  this->premises.value(start)->setSourceNode();
  this->premises.value(goal)->setDestinationNode();

  // clear shortest path
  this->shortest.clear();

  // inf
  const double inf = 1e+99;

  // initial empty visited
  QVector<int> checked;

  // set all distances to inf
  foreach(Node *n, this->premises) {
      n->setG(inf);
  }
  // set start G value to  0.0
  this->premises.value(start)->setG(0.0);

  // initial que contains all
  QVector<int> que;

  // fill que
  for ( int k = 0; k < this->premises.count(); k++ ) {
    Node *node_access = this->premises.value(k);
    if ((node_access->getWalk() && walk) ||
        (node_access->getVehicle() && vehicle) ||
        (node_access->getWheelChair() && wheelchair) ||
        (node_access->getBike() && bicycle) )
        que.push_back(k);
  }
  // wait while the whole que is empty ( this may be ineffective )
  while ( que.count() > 0 ) {
    // initialize the curren index,
    // the index to be removed and the current min G value
    int current_index = -1;
    int remove_index = -1;
    double current_min = inf;

    // select the next value with the lowest G value
    for ( int l = 0; l < que.count(); l++ ) {
        if ( this->premises.value(l)->getG() < current_min ) {
          current_min = this->premises.value(l)->getG();
          current_index = que.value(l);
          remove_index = l;
        }
    }
    // remove current checked
    if ( remove_index > -1 )
      que.remove(remove_index);
    else
      break;

    // mark node as checked
    if ( current_index > -1 ) {
      checked.push_back(current_index);
      const int count_connected = this->
                                  premises.value(current_index)->
                                  countConnected();
      // check all the neighbor nodes
      for ( int p = 0; p < count_connected; p++ ) {
        // calculate the distance between current
        // node and the current active neigbor node
        QVector3D point = this->
                           premises.value(current_index)->
                           Position();
        double nodedist = this->
                          premises.value(this->
                               premises.value(current_index)->
                               getConnectedIndex(p))->
                               Position().distanceToPoint(point);

          // replace the node's shortest current path if needed.
          // (dist(v,u) + g(v)< g(u))
          if ( nodedist + this->premises.value(current_index)->getG()
             <= this->premises.value(this->
                              premises.value(current_index)->
                              getConnectedIndex(p))->
                              getG() ) {
            // update the g value and shortest path of the neighbor

            this->premises.value(this->premises.value(current_index)->
                                 getConnectedIndex(p))->
                                 setG(nodedist + this->
                                                 premises.value(current_index)->
                                                 getG());
            this->premises.value(this->premises.value(current_index)->
                                 getConnectedIndex(p))->
                                 setShortest(current_index);
          }
       }
    } else {
        break;
    }

  }

  // list path
  int _back_node = goal;
  if ( this->premises.value(_back_node)->getShortestIndex() > -1 ) {
    // add the first node to the list
    this->shortest.push_back(_back_node);
    // assign the loop control variable.
    // this variable checks for loops within the mesh
    _back_node = this->premises.value(_back_node)->getShortestIndex();
    int loop_var = _back_node;
    if ( _back_node > -1 ) {
      // add another index
      this->shortest.push_back(_back_node);
    }
    while ( _back_node != start ) {
      int error = _back_node;
      // backwards trace the shortest path
      _back_node = this->premises.value(_back_node)->getShortestIndex();
      if ( _back_node > -1 ) {
        if ( this->shortest.value(this->shortest.count() - 1 ) != _back_node) {
          this->shortest.push_back(_back_node);
        } else {
          return -1;
        }
      } else {
        return error;
      }
      if ( _back_node == loop_var) {
          return loop_var;      }
    }

  }
  if ( _back_node == start )
   return -1;
  else {
   return _back_node;
  }
}

int NodeHandler::pathcount() {
    return this->shortest.count();
}

int NodeHandler::pathindex(int index) {
    return this->shortest.value(index);
}

void NodeHandler::ReadFilePVC(QString filename) {
  QVector<int> walk, wheelchair, vehice, bicycle;
  // clear the premises when not empty
  if ( this->premises.count() > 0 )
    this->premises.clear();

  /* populate the premisis from the text file */
  // load the text file
  QFile textfile(filename);

  // open the text file
  textfile.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream ascread(&textfile);

  if ( textfile.isOpen() ) {
    // read each line of the file
    QString line = ascread.readLine();
    while ( !line.isNull() ) {
      // break the line up in usable parts
      QStringList list = line.split(",");
      // check the type of line
      /* n-> node
         j-> join */
      if ( list[0] == "n" ) {
          // this is only x, y, z coordinates for the node
          float vertex[3];
          int signi = 0;
          QString display_name ="";
          // populate the vertices
          for ( int i = 0; i < 3; i++ )
               QTextStream(&list[i+2]) >> vertex[i];

          // get node significance
          QTextStream(&list[6]) >> signi;
          // get the node's name
          display_name = list[5];
          Node* n = new Node(new QVector3D(vertex[0],
                                           vertex[1],
                                           vertex[2]));
          // set node's significance
          n->setSignificant((signi == 1));

          // set node's name
          n->setName(display_name);

          AddNode(n);
      } else if ( list[0] == "j" ) {
                // this is only the indices that should be join
                int uv[2];
                // populate the indices
                for ( int i = 0; i < 2; i++ )
                  QTextStream(&list[i+1]) >> uv[i];
                // add the links
                AddNodeLinkbyIndex(uv[0], uv[1]);
      } else if ( list[0] == "wc" ) {
          if(list.count() > 1)
          wheelchair.append(list[1].toInt());
      } else if ( list[0] == "vi" ) {
          if(list.count() > 1)
          vehice.append(list[1].toInt());
      } else if ( list[0] == "ft" ) {
          if(list.count() > 1)
          walk.append(list[1].toInt());
      } else if ( list[0] == "by" ) {
          if(list.count() > 1)
          bicycle.append(list[1].toInt());
      }
      // read next line
      line = ascread.readLine();
    }
    // close the textfile
    textfile.close();
  }
  // add walkable nodes
  for ( int i = 0; i < walk.count(); i++) {
      this->premises.value(walk.value(i))->setWalk(true);
  }
  // add wheelchair nodes
  for ( int i = 0; i < wheelchair.count(); i++) {
      this->premises.value(wheelchair.value(i))->setWheelChair(true);
  }
  // add vehicle nodes
  for ( int i = 0; i < vehice.count(); i++) {
      this->premises.value(vehice.value(i))->setVehicle(true);
  }
  // add bicycle nodes
  for ( int i = 0; i < bicycle.count(); i++) {
      this->premises.value(bicycle.value(i))->setBike(true);
  }
}
