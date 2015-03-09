#ifndef NODEHANDLER_H
#define NODEHANDLER_H
#include "VCCMObjects/Node.h"
#include <QVector>
#include <QString>
#include <qdebug.h>
class NodeHandler
{
public:
    NodeHandler();
    void AddNode(Node*);
    Node NodeFromIndex(unsigned int);
    void AddNodeLink(int,QString*);
    void AddNodeLinkbyIndex(int,int);
    int count();
private:
    QVector<Node*> m_premises;
};

#endif // NODEHANDLER_H
