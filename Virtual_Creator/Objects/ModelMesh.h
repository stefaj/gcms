#ifndef MODELMESH_H
#define MODELMESH_H
#include <QVector>

class QVector2D;
class QVector3D;
class QString;

class ModelMesh{
public:
    ModelMesh(QString);
    ~ModelMesh();
    void Draw();
    QVector<QVector2D> textureCoordinates;
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<int> vertexIndices, uvIndices, normalIndices;
    bool LoadOBJ(QString);
};

#endif // MODELMESH_H
