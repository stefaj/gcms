/* Copyright 2015 Ruan Luies */

#include "Objects/visualobject.h"

VisualObject::VisualObject(ModelMesh * model,
                           QOpenGLTexture *texture,
                           QVector3D translation,
                           QVector3D rotation,
                           QString type) {
     this->model = model;
     this->texture = texture;
     this->translation = translation;
     this->rotation = rotation;
     this->type = type;
     this->corner_1 = translation;
     this->corner_2 = translation;
     this->corner_3 = translation;
     this->corner_4 = translation;
     this->center_h_1 = translation;
     this->center_h_2 = translation;
}

void VisualObject::setModel(ModelMesh* model) {
    this->model = model;
}

void VisualObject::setRotation(QVector3D rotation) {
    this->rotation = rotation;
}

void VisualObject::setTranslation(QVector3D translation) {
    this->translation = translation;
}

void VisualObject::setScaling(QVector3D scale) {
    this->scaling = scale;
}

void VisualObject::setTexture(QOpenGLTexture *texture) {
    this->texture = texture;
}

QVector3D VisualObject::getRotation() {
    return this->rotation;
}

QVector3D VisualObject::getTranslation() {
    return this->translation;
}

QVector3D VisualObject::getScaling() {
    return this->scaling;
}

ModelMesh * VisualObject::getModelMesh() {
    return this->model;
}

QOpenGLTexture * VisualObject::getTexture() {
    return this->texture;
}

QString VisualObject::getType() {
    return this->type;
}

void VisualObject::setCornerULeft(QVector3D value) {
    this->corner_1 = value;
}

void VisualObject::setCornerURight(QVector3D value) {
    this->corner_2 = value;
}

void VisualObject::setCornerLLeft(QVector3D value) {
    this->corner_3 = value;
}

void VisualObject::setCornerLRight(QVector3D value) {
    this->corner_4 = value;
}

void VisualObject::setUMidHorisontal(QVector3D value) {
    this->center_h_2 = value;
}

void VisualObject::setLMidHorisontal(QVector3D value) {
    this->center_h_1 = value;
}

void VisualObject::setTextureID(int value) {
    this->texture_id = value;
}

void VisualObject::setTexturePath(QString value) {
    this->path_texture = value;
}

QVector3D VisualObject::getCornerULeft() {
    return this->corner_1;
}

QVector3D VisualObject::getCornerURight() {
    return this->corner_2;
}

QVector3D VisualObject::getCornerLLeft() {
    return this->corner_3;
}

QVector3D VisualObject::getCornerLRight() {
    return this->corner_4;
}

QVector3D VisualObject::getUMidHorisontal() {
    return this->center_h_1;
}

QVector3D VisualObject::getLMidHorisontal() {
    return this->center_h_2;
}

void VisualObject::setType(QString type) {
    this->type = type;
}

int VisualObject::getTextureID() {
    return this->texture_id;
}

QString VisualObject::getTexturePath() {
    return this->path_texture;
}

VisualObject::~VisualObject() {
  delete this->model;
  delete this->texture;
}

