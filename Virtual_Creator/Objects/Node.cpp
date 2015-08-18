/* Copyright 2015 Ruan Luies */

#include "Objects/Node.h"
#include <QVector2D>
#include <QVector3D>
#include <QString>

Node::Node() {
    this->position = new QVector3D(0, 0, 0);
    this->color = new QVector3D(0, 0, 0);
    this->name = new QString();
    this->connected.clear();
    this->connectedindex.clear();
    this->shortest.clear();
    this->links = false;
    this->walk = false;
    this->bike = false;
    this->vehicle = false;
    this->wheelchair = false;
    this->significant = true;
    this->nshortest = 0;
    this->g = 99999999999999.0;
    this->lastindex = 0;
}

Node::Node(QVector3D * Position) {
    this->position = Position;
    this->color = new QVector3D(0, 0, 0);
    this->name = new QString();
    this->connected.clear();
    this->connectedindex.clear();
    this->shortest.clear();
    this->links = false;
    this->nshortest = -1;
    this->g = 99999999999999.0;
}

void Node::setName(QString value) {*this->name = value;}

QVector3D Node::getColor() {return *this->color;}

void Node::setColor(QVector3D *color) {this->color = color;}

Node::Node(QVector3D *Position, QString *Name) {
    this->position = Position;
    this->name = Name;
    this->color = new QVector3D(0, 0, 0);
    this->connected.clear();
    this->connectedindex.clear();
    this->shortest.clear();
    this->links = false;
    this->nshortest = -1;
    this->g = 99999999999999.0;
}

void Node::setSourceNode() {
    this->color->setX(0.0f);
    this->color->setY(0.0f);
    this->color->setZ(1.0f);
}

void Node::setDestinationNode() {
    this->color->setX(1.0f);
    this->color->setY(0.0f);
    this->color->setZ(0.0f);
}

void Node::AddLink(QString *Name, int index) {
    if ( !this->connectedindex.contains(index) ) {
        this->connected.push_back(Name);
        this->connectedindex.push_back(index);
        this->links = true;
    }
}

void Node::RemoveLinkedFromIndex(int index) {
    if ( index > this->connected.count() ) {
      this->connected.removeAt(index);
      this->connectedindex.removeAt(index);
    }
    if ( this->connected.count() < 1 )
        this->links = false;
}

void Node::MoveLinkedIndexBack(int index) {
  // replace the specific index
  if ( this->connectedindex.value(index) > 0 )
  this->connectedindex.replace(index,
                               this->connectedindex.value(index) - 1);
}

QVector3D Node::Position() {return *this->position;}

int Node::countConnected() {return this->connected.size();}

QString Node::getLinkedName(int index) {
    return *this->connected.value(index);
}

int Node::getConnectedIndex(int index) {
    return this->connectedindex.value(index);
}

QString Node::getName() {return *this->name;}

void Node::clearPath() {this->shortest.clear();}

void Node::addShortest(int index) {this->shortest.push_back(index);}

void Node::setG(double g) {this->g = g;}

double Node::getG() {return this->g;}

void Node::setShortest(int index) {this->nshortest = index;}

int Node::getShortestIndex() {return this->nshortest;}

void Node::setWalk(bool value) {this->walk = value;}

void Node::setWheelChair(bool value) {this->wheelchair = value;}

void Node::setVehicle(bool value) {this->vehicle = value;}

void Node::setBike(bool value) {this->bike = value;}

void Node::setSignificant(bool value) {this->significant = value;}

bool Node::getWalk() {return this->walk;}

bool Node::getWheelChair() {return this->wheelchair;}

bool Node::getVehicle() {return this->vehicle;}

bool Node::getBike() {return this->bike;}

bool Node::getSignificant() {return this->significant;}

