/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_OBJECTS_MODELMESH_H_
#define VIRTUAL_CREATOR_OBJECTS_MODELMESH_H_

#include <QVector>

class QVector2D;
class QVector3D;
class QString;

class ModelMesh {
 public:
    explicit ModelMesh(QString filename);
    ~ModelMesh();
    void Draw();
    QVector<QVector2D> texture_coordinates;
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<int> vertex_indices, uv_indices, normal_indices;
    bool LoadOBJ(QString filename);
};

#endif  // VIRTUAL_CREATOR_OBJECTS_MODELMESH_H_
