#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

class Camera
{
public:
  Camera();

private:
  QVector3D position ;
  QMatrix4x4 transformation;
  QVector3D center;
  QVector3D up;
};

#endif // CAMERA_H
