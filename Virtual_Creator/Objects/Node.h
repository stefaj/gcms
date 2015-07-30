/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_OBJECTS_NODE_H_
#define VIRTUAL_CREATOR_OBJECTS_NODE_H_

#include <QVector>
class QVector2D;
class QVector3D;
class QString;
class Node {
 public:
    Node();
    explicit Node(QVector3D * position);
    Node(QVector3D* position, QString* name);
    // index from other node
    void AddLink(QString* name, int index);
    QVector3D Position();
    QVector3D getColor();
    void setSourceNode();
    void setDestinationNode();
    void setColor(QVector3D * rgb);
    int countConnected();
    int getConnectedIndex(int index);
    void RemoveLinkedFromIndex(int index);
    void MoveLinkedIndexBack(int index);
    QString getLinkedName(int index);
    void clearPath();
    void addShortest(int index);
    void setG(double g);
    void setName(QString);
    void setShortest(int index);
    void setWalk(bool can_walk);
    void setWheelChair(bool can_use_wheelchair);
    void setVehicle(bool can_use_vehicle);
    void setBike(bool can_use_bike);
    void setSignificant(bool is_significant);
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

#endif  // VIRTUAL_CREATOR_OBJECTS_NODE_H_
