/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_FUNCTIONS_MATHEMATICS_H_
#define VIRTUAL_CREATOR_FUNCTIONS_MATHEMATICS_H_

#include <QVector3D>
#include <QVector4D>
#include <QPoint>
#include <QMatrix4x4>

class Mathematics {
public:
    Mathematics();
    ~Mathematics();
    static QVector3D intersectYnull(QVector3D raycast_vector,
                                    QVector3D camera_position);
    static QVector3D intersectYat(QVector3D raycast_vector,
                                  QVector3D camera_position,
                                  float y_intersect_plane);
    static float flat_angle_from_vectors(QVector3D vector_a,
                                         QVector3D vector_b);
    static float return_near_degree(float degrees);
    static QVector3D mouse_raycast(int mouse_x,
                                   int mouse_y,
                                   int screen_width,
                                   int screen_height,
                                   float invert_sign,
                                   QMatrix4x4 view_matrix,
                                   QMatrix4x4 projection_matrix);
    static QVector3D point_on_line(float x,
                                   QVector3D point_a,
                                   QVector3D point_b);
    static QPoint transform_3d_to_2d(QMatrix4x4 view_matrix,
                                     QMatrix4x4 projection_matrix,
                                     QVector3D point,
                                     int screen_width,
                                     int screen_height);
    static bool detect_point_in_plan_on_y(QVector3D position,
                                          QVector3D scale,
                                          float rotation_z,
                                          QVector3D intersection_point);
    static bool detect_point_near_line(QVector3D point_a,
                                       QVector3D point_b,
                                       QVector3D position,
                                       float threshhold);
};

#endif  // VIRTUAL_CREATOR_FUNCTIONS_MATHEMATICS_H_
