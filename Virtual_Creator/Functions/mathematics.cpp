#include "mathematics.h"
#include <QtMath>

Mathematics::Mathematics(){

}

QVector3D Mathematics::intersectYnull(QVector3D u_dir, QVector3D r_point){
    float t =0.0;//t determines the point of intersection
    if(u_dir.y() != 0)// (1/0) validation
    t = -r_point.y()/u_dir.y(); // t=-r1.y/r (calculus)
    return r_point+t*u_dir;// v(t)=r+t*r1
}

float Mathematics::flat_angle_from_vectors(QVector3D pointA, QVector3D pointB){
    float delta_x = pointB.x()-pointA.x();
    float delta_z = pointB.z()-pointA.z();
    float distance = pointA.distanceToPoint(pointB);
    // get the angle from the arccos function
    if(delta_z>0)
    return -(180*acos(delta_x/distance)/(3.141592));
    else
        return (180*acos(delta_x/distance)/(3.141592));
}

float Mathematics::return_near_degree(float value){
    // clamping factor
    const float diff = 2.0f;

    // if the degrees are near 45, clamp to 45 degrees
    if((value-diff <45) &&(value+diff >45) )
        return 45.0f;

    // if the degrees are near 90, clamp to 90 degrees
    if((value-diff <90) &&(value+diff >90) )
        return 90.0f;

    // if the degrees are near 180, clamp to 180 degrees
    if((value-diff < 180) &&(value+diff > 180) )
        return 180.0f;

    // if the degrees are near -45, clamp to -45 degrees
    if((value-diff < -45) &&(value+diff > -45) )
        return -45.0f;

    // if the degrees are near -90, clamp to -90 degrees
    if((value-diff > -90) &&(value+diff < -90) )
        return -90.0f;

    // if the degrees are near 270, clamp to 270 degrees
    if((value-diff < 270) &&(value+diff > 270) )
        return 270.0f;

    // if the degrees are near 0, clamp to 0 degrees
    if((value-diff < 0) &&(value+diff > 0) )
        return 0.0f;

    // else return the normal value unchanged
    return value;
}

QVector3D Mathematics::mouse_raycast(int mx, int my, int width, int height, float invertedy, QMatrix4x4 view_matrix, QMatrix4x4 projection_matrix){
    float nx = (2.0f * mx) / width - 1.0f; // normalize the x-mouse position
    float ny = invertedy*(1.0f - (2.0f * my) / height);// normalize the y-mouse position
    QVector4D ray_clip = QVector4D(nx,ny,-1,1.0); // clip the x,y,z values between -1:1
    QMatrix4x4 pInverse = projection_matrix.inverted(NULL);// invert the projection
    QMatrix4x4 vInverse = view_matrix.inverted(NULL);// invert the view
    QVector4D ray_eye = pInverse*ray_clip; // "convert" the normalized ray to the projection values
    ray_eye = QVector4D(ray_eye.x(),ray_eye.y(),-1.0,0);// change the w-value of the vector for matrix manipulation purposes
    QVector4D ray_wor4 = vInverse*ray_eye; // "convert" the new ray to the view values
    QVector3D ray_wor = ray_wor4.toVector3D(); // take the x,y,z values of the new position
    ray_wor.normalize();// make the ray a unit vector
    return ray_wor; // return the raycast of the 2D mouse in the 3D world view projection
}

QVector3D Mathematics::point_on_line(float x, QVector3D pointA,QVector3D pointB){
    const float slope = (pointA.z()-pointB.z())/(pointA.x()-pointB.x());
    return QVector3D(x,0,x*slope+(pointA.z()-slope*pointA.x()));
}

Mathematics::~Mathematics(){

}

