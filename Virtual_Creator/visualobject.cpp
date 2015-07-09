#include "visualobject.h"

VisualObject::VisualObject(ModelMesh * model, QOpenGLTexture *texture, QVector3D translation, QVector3D rotation)
{
 m_model = model;
 m_texture = texture;
 m_translation = translation;
 m_rotation = rotation;
}
void VisualObject::setModel(ModelMesh* model){ m_model = model;}

void VisualObject::setRotation(QVector3D){}

void VisualObject::setTranslation(QVector3D){}

void VisualObject::setScaling(QVector3D){}

void VisualObject::setTexture(QOpenGLTexture *texture){ m_texture = texture;}

QVector3D VisualObject::getRotation(){return m_rotation;}

QVector3D VisualObject::getTranslation(){return m_translation;}

QVector3D VisualObject::getScaling(){return m_scaling;}

ModelMesh * VisualObject::getModelMesh(){return m_model;}

QOpenGLTexture *VisualObject::getTexture(){return m_texture;}

VisualObject::~VisualObject()
{
 delete m_model;
}

