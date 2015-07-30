#ifndef NODE_H
#define NODE_H
#include <QVector>

class QVector2D;
class QVector3D;
class QString;
class Node{
public:
    Node();
    Node(QVector3D *);
    Node(QVector3D *, QString *);
    void AddLink(QString *,int); // index from other node
    QVector3D Position();
    QVector3D getColor();
    void setSourceNode();
    void setDestinationNode();
    void setColor(QVector3D *);
    int countConnected();
    int getConnectedIndex(int index);
    void RemoveLinkedFromIndex(int);
    void MoveLinkedIndexBack(int);
    QString getLinkedName(int);
    void clearPath();
    void addShortest(int);
    void setG(double g);
    void setName(QString);
    void setShortest(int index);
    void setWalk(bool);
    void setWheelChair(bool);
    void setVehicle(bool);
    void setBike(bool);
    void setSignificant(bool);
    bool getWalk();
    bool getWheelChair();
    bool getVehicle();
    bool getBike();
    bool getSignificant();
    int getShortestIndex();
    double getG();
    QString getName();
private:
    QVector3D *position;
    QString *name;
    QVector3D *color;
    QVector<QString*> connected;
    QVector<int> connectedindex;
    QVector<int> shortest;
    int nshortest;
    double g;
    bool links, walk, wheelchair, vehicle, bike, significant;
    int lastindex;
};

#endif // NODE_H
