#include "visualobject.h"

VisualObject::VisualObject(ModelMesh * model, QOpenGLTexture *texture, QVector3D translation, QVector3D rotation, QString type)
{
     m_model = model;
     m_texture = texture;
     m_translation = translation;
     m_rotation = rotation;
     m_type = type;
     m_corner_1 = translation;
     m_corner_2 = translation;
     m_corner_3 = translation;
     m_corner_4 = translation;
     m_center_h_1 = translation;
     m_center_h_2 = translation;
}

void VisualObject::setModel(ModelMesh* model){ m_model = model;}

void VisualObject::setRotation(QVector3D rotation){ m_rotation = rotation;}

void VisualObject::setTranslation(QVector3D translation){ m_translation = translation;}

void VisualObject::setScaling(QVector3D scale){ m_scaling = scale;}

void VisualObject::setTexture(QOpenGLTexture *texture){ m_texture = texture;}

QVector3D VisualObject::getRotation(){return m_rotation;}

QVector3D VisualObject::getTranslation(){return m_translation;}

QVector3D VisualObject::getScaling(){return m_scaling;}

ModelMesh * VisualObject::getModelMesh(){return m_model;}

QOpenGLTexture * VisualObject::getTexture(){return m_texture;}

QString VisualObject::getType(){return m_type;}

void VisualObject::setCornerULeft(QVector3D value){ m_corner_1 = value;}

void VisualObject::setCornerURight(QVector3D value){m_corner_2 = value;}

void VisualObject::setCornerLLeft(QVector3D value){m_corner_3 = value;}

void VisualObject::setCornerLRight(QVector3D value){m_corner_4 = value;}

void VisualObject::setUMidHorisontal(QVector3D value){m_center_h_2 = value;}

void VisualObject::setLMidHorisontal(QVector3D value){m_center_h_1 = value;}

QVector3D VisualObject::getCornerULeft(){ return m_corner_1;}

QVector3D VisualObject::getCornerURight(){return m_corner_2;}

QVector3D VisualObject::getCornerLLeft(){return m_corner_3;}

QVector3D VisualObject::getCornerLRight(){return m_corner_4;}

QVector3D VisualObject::getUMidHorisontal(){return m_center_h_1;}

QVector3D VisualObject::getLMidHorisontal(){return m_center_h_2;}

void VisualObject::setType(QString type){m_type = type;}

VisualObject::~VisualObject()
{
 delete m_model;
 delete m_texture;
}

