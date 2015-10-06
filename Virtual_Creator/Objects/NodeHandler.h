/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_OBJECTS_NODEHANDLER_H_
#define VIRTUAL_CREATOR_OBJECTS_NODEHANDLER_H_

#include <QVector>
#include <QString>
#include <qdebug.h>
#include "Objects/Node.h"

class QVector3D;
class NodeHandler {
 public:
    NodeHandler();
    void AddNode(Node* node);
    Node NodeFromIndex(unsigned int index);

    void AddNodeLink(int index, QString* name);
    void AddNodeLinkbyIndex(int index1, int index2);
    int CalculateShortest(int start,
                          int finish,
                          bool walk,
                          bool wheelchair,
                          bool vehicle,
                          bool bicycle);
    void ReadFilePVC(QString filename);
    int count();
    int pathcount();
    int pathindex(int shortest_index);
    QString DisplayError();
    void AddNodes(QVector<Node*> nodes);
    QVector<int> error_nodes_indices();
 private:
    QVector<Node*> premises;
    QVector<int> shortest;
};

#endif  // VIRTUAL_CREATOR_OBJECTS_NODEHANDLER_H_
