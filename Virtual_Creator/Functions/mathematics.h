#ifndef MATHEMATICS_H
#define MATHEMATICS_H
#include <QVector3D>
#include <QVector4D>
#include <QPoint>
#include <QMatrix4x4>

class Mathematics{
public:
    Mathematics();
    ~Mathematics();
    static QVector3D intersectYnull(QVector3D, QVector3D);
    static QVector3D intersectYat(QVector3D,QVector3D,float);
    static float flat_angle_from_vectors(QVector3D, QVector3D);
    static float return_near_degree(float);
    static QVector3D mouse_raycast(int, int, int, int, float, QMatrix4x4, QMatrix4x4);
    static QVector3D point_on_line(float, QVector3D, QVector3D);
    static QPoint transform_3d_to_2d(QMatrix4x4,QMatrix4x4,QVector3D,int,int);
};

#endif // MATHEMATICS_H
