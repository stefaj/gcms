/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_OBJECTS_VISUALOBJECT_H_
#define VIRTUAL_CREATOR_OBJECTS_VISUALOBJECT_H_

#include <QVector3D>
#include <QMatrix>
#include <QOpenGLTexture>
#include <Objects/ModelMesh.h>

class VisualObject {
 public:
    VisualObject(ModelMesh* modelmesh,
                 QOpenGLTexture* texture,
                 QVector3D translation,
                 QVector3D rotation,
                 QString type);
    ~VisualObject();
    void setModel(ModelMesh* modelmesh);
    void setRotation(QVector3D rotation);
    void setTranslation(QVector3D translation);
    void setTexture(QOpenGLTexture* texture);
    void setScaling(QVector3D scale);
    void setCornerULeft(QVector3D position);
    void setCornerURight(QVector3D position);
    void setCornerLLeft(QVector3D position);
    void setCornerLRight(QVector3D position);
    void setUMidHorisontal(QVector3D position);
    void setLMidHorisontal(QVector3D position);
    void setTextureID(int index);
    void setTexturePath(QString filename);
    QVector3D getCornerULeft();
    QVector3D getCornerURight();
    QVector3D getCornerLLeft();
    QVector3D getCornerLRight();
    QVector3D getUMidHorisontal();
    QVector3D getLMidHorisontal();
    QVector3D getRotation();
    QVector3D getTranslation();
    QVector3D getScaling();
    ModelMesh* getModelMesh();
    QOpenGLTexture* getTexture();
    QString getType();
    QString getTexturePath();
    int getTextureID();
    void setType(QString type);

 private:
    ModelMesh *model;
    QVector3D translation, rotation, scaling;
    QOpenGLTexture *texture;
    int texture_id;
    QString path_texture;
    QString type;
    QVector3D corner_1, corner_2, corner_3, corner_4, center_h_1, center_h_2;
};

#endif  // VIRTUAL_CREATOR_OBJECTS_VISUALOBJECT_H_
