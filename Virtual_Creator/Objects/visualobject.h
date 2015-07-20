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
    void setCornerULeft(QVector3D);
    void setCornerURight(QVector3D);
    void setCornerLLeft(QVector3D);
    void setCornerLRight(QVector3D);
    void setUMidHorisontal(QVector3D);
    void setLMidHorisontal(QVector3D);
    void setTextureID(int);
    void setTexturePath(QString);
    QVector3D getCornerULeft();
    QVector3D getCornerURight();
    QVector3D getCornerLLeft();
    QVector3D getCornerLRight();
    QVector3D getUMidHorisontal();
    QVector3D getLMidHorisontal();
    QVector3D getRotation();
    QVector3D getTranslation();
    QVector3D getScaling();
    ModelMesh * getModelMesh();
    QOpenGLTexture *getTexture();
    QString getType();
    QString getTexturePath();
    int getTextureID();
    void setType(QString);
private:
    ModelMesh *m_model;
    QVector3D m_translation, m_rotation, m_scaling;
    QOpenGLTexture *m_texture;
    int m_texture_id;
    QString m_path_texture;
    QString m_type;
    QVector3D m_corner_1, m_corner_2, m_corner_3, m_corner_4, m_center_h_1, m_center_h_2;

};

#endif // VISUALOBJECT_H
