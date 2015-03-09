/** *********************************************************************** **/
/** *********************************************************************** **/
/**     Created by:     Ruan (Baggins) Luies 23511354                       **/
/**     email:          23511354@nwu.ac.za                                  **/
/**     Project name:   Virtual Concierge Creator And Management System     **/
/**     File Name:      Node.h                                              **/
/**     From Date:      2015/02/24                                          **/
/**     To Date:        2015/10/01                                          **/
/** **********************************************************************  **/
/** *********************************************************************** **/

#ifndef NODE_H
#define NODE_H
#include <QVector>

class QVector2D;
class QVector3D;
class QString;
class Node
{
public:
    Node();
    Node(QVector3D *);
    Node(QVector3D *, QString *);
    void AddLink(QString *);
    QVector3D Position();
    int countConnected();
    QString getLinkedName(int);
    QString getName();
private:
    QVector3D *m_position;
    QString *m_name;
    QVector<QString*> m_connected;
    bool m_links;
};

#endif // NODE_H
