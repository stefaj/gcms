#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H
#include <Objects/ModelMesh.h>
#include <QVector3D>
#include <QMatrix>
#include <QOpenGLTexture>

class VisualObject
{
public:
    VisualObject(ModelMesh*,QOpenGLTexture*,QVector3D,QVector3D,QString);
    ~VisualObject();
    void setModel(ModelMesh*);
    void setRotation(QVector3D);
    void setTranslation(QVector3D);
    void setTexture(QOpenGLTexture*);
    void setScaling(QVector3D);
    QVector3D getRotation();
    QVector3D getTranslation();
    QVector3D getScaling();
    ModelMesh * getModelMesh();
    QOpenGLTexture *getTexture();
    QString getType();
    void setType(QString);

private:
    ModelMesh *m_model;
    QVector3D m_translation, m_rotation, m_scaling;
    QOpenGLTexture *m_texture;
    QString m_type;

};

#endif // VISUALOBJECT_H
