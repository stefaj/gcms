#include "camera.h"

Camera::Camera()
{

    this->transformation.rotate(0, 0, 1, 0);
    // rotation in the x - axis
    this->transformation.rotate(-90, 1, 0, 0);

    this->up = this->transformation *
            QVector3D(0, 1, 0);

    QVector3D e = QVector3D(0,0,1);
    this->position = this->transformation * e;



}
