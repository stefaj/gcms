/* Copyright 2015 Ruan Luies */

#include <QtMath>
#include <QDebug>
#include "./mathematics.h"

Mathematics::Mathematics() {
}

QVector3D Mathematics::intersectYnull(QVector3D u_dir,
                                      QVector3D r_point) {
  float t = 0.0;  // t determines the point of intersection
  if ( u_dir.y() != 0 )  // (1/0) validation
    t = -r_point.y() / u_dir.y();  // t=-r1.y/r (calculus)
  return r_point + t * u_dir;  // v(t)=r+t*r1
}

float Mathematics::flat_angle_from_vectors(QVector3D pointA,
                                           QVector3D pointB) {
  float delta_x = pointB.x()-pointA.x();
  float delta_z = pointB.z()-pointA.z();
  float distance = pointA.distanceToPoint(pointB);
  // get the angle from the arccos function
  if ( delta_z > 0)
    return -(180*acos(delta_x/distance)/(3.141592));
  else
    return (180*acos(delta_x/distance)/(3.141592));
}

QVector3D Mathematics::intersectYat(QVector3D u_dir,
                                    QVector3D r_point,
                                    float y) {
  float t = 0.0;  // t determines the point of intersection
  if ( u_dir.y() != 0 )  // (1/0) validation
    t = -r_point.y() / u_dir.y();  // t=-r1.y/r (calculus)
  return r_point + t * u_dir + QVector3D(0, y, 0);  // v(t)=r+t*r1
}

float Mathematics::return_near_degree(float value) {
  // clamping factor
  const float diff = 2.0f;

  // if the degrees are near 45, clamp to 45 degrees
  if ( (value - diff < 45) && (value + diff >45) )
    return 45.0f;

  // if the degrees are near 90, clamp to 90 degrees
  if ( (value - diff < 90) && (value + diff >90) )
    return 90.0f;

  // if the degrees are near 180, clamp to 180 degrees
  if ( (value - diff < 180) && (value + diff > 180) )
    return 180.0f;

  // if the degrees are near -45, clamp to -45 degrees
  if ( (value - diff < -45) && (value + diff > -45) )
    return -45.0f;

  // if the degrees are near -90, clamp to -90 degrees
  if ( (value - diff > -90) && (value + diff < -90) )
    return -90.0f;

  // if the degrees are near 270, clamp to 270 degrees
  if ( (value - diff < 270) && (value + diff > 270) )
    return 270.0f;

  // if the degrees are near 0, clamp to 0 degrees
  if ( (value - diff < 0) && (value + diff > 0) )
    return 0.0f;

  // else return the normal value unchanged
  return value;
}

QVector3D Mathematics::mouse_raycast(int mx,
                                     int my,
                                     int width,
                                     int height,
                                     float invertedy,
                                     QMatrix4x4 view_matrix,
                                     QMatrix4x4 projection_matrix) {
  // normalize the x-mouse position
  float nx = (2.0f * mx) / width - 1.0f;
  // normalize the y-mouse position
  float ny = invertedy*(1.0f - (2.0f * my) / height);
  // clip the x,y,z values between -1:1
  QVector4D ray_clip = QVector4D(nx, ny, -1, 1.0);
  // invert the projection
  QMatrix4x4 pInverse = projection_matrix.inverted(NULL);
  // invert the view
  QMatrix4x4 vInverse = view_matrix.inverted(NULL);
  // "convert" the normalized ray to the projection values
  QVector4D ray_eye = pInverse*ray_clip;
  // change the w-value of the vector for matrix manipulation purposes
  ray_eye = QVector4D(ray_eye.x(), ray_eye.y(), -1.0, 0);
  // "convert" the new ray to the view values
  QVector4D ray_wor4 = vInverse*ray_eye;
  // take the x,y,z values of the new position
  QVector3D ray_wor = ray_wor4.toVector3D();
  ray_wor.normalize();  // make the ray a unit vector
  // return the raycast of the 2D mouse in the 3D world view projection
  return ray_wor;
}

QVector3D Mathematics::point_on_line(float x,
                                     QVector3D pointA,
                                     QVector3D pointB) {
  const float slope = (pointA.z() - pointB.z()) / (pointA.x() - pointB.x());
  return QVector3D(x, 0, x * slope + (pointA.z() - slope * pointA.x()));
}

QPoint Mathematics::transform_3d_to_2d(QMatrix4x4 view,
                                       QMatrix4x4 projection,
                                       QVector3D point,
                                       int width,
                                       int height) {
  QMatrix4x4 view_proj = projection * view;
  // transform world to clipping coordinates
  QVector3D p = view_proj * point;
  int x = static_cast<int>(qRound((((p.x() + 1.0)/2.0) * width)));
  int y = static_cast<int>(qRound((((1.0 - p.y())/2.0) * height)));
  return QPoint(x, y);
}

bool Mathematics::detect_point_in_plan_on_y(QVector3D position,
                                            QVector3D scale,
                                            float rotation_y,
                                            QVector3D intersection_point) {
  const float pi = 3.141592653589798;
  float rotation_in_radians_t_l = (rotation_y + 135) * (pi / 180.0) ;
  float rotation_in_radians_t_r = (rotation_y + 45) * (pi / 180.0) ;
  float rotation_in_radians_b_l = (rotation_y - 135) * (pi / 180.0) ;
  float rotation_in_radians_b_r = (rotation_y - 45) * (pi / 180.0) ;
  float distance = pow(scale.x()*scale.x() + scale.z()*scale.z(), 0.5) / 2.0;
  bool no_rotation = false;
  float z_1, z_2, z_3, z_4;
  QVector3D position_top_left,
      position_top_right,
      position_bot_left,
      position_bot_right;
  position_top_left = position +
                      QVector3D(distance * cos(rotation_in_radians_t_l),
                                0,
                                distance * sin(rotation_in_radians_t_l) );
  position_top_right = position +
                       QVector3D(distance * cos(rotation_in_radians_t_r),
                                 0,
                                 distance * sin(rotation_in_radians_t_r));
  position_bot_left = position +
                      QVector3D(distance * cos(rotation_in_radians_b_l),
                                0,
                                distance * sin(rotation_in_radians_b_l));
  position_bot_right = position +
                       QVector3D(distance * cos(rotation_in_radians_b_r),
                                 0,
                                 distance * sin(rotation_in_radians_b_r));
  if ( (round ( position_top_left.x() - position_top_right.x() ) == 0)||
       (round ( position_bot_left.x() - position_bot_right.x() ) == 0)||
       (round ( position_bot_right.x() - position_top_right.x() ) == 0)||
       (round ( position_top_left.x() - position_bot_left.x() ) == 0) ) {
    no_rotation = true;
  } else {
    // calculate the constants ( there are 4 in total )
    float c_1, c_2, c_3, c_4;
    // slopes ( 2 of the four slopes are the same )
    float m_1 = (position_top_left.z() - position_top_right.z())
                / (position_top_left.x() - position_top_right.x()),
        m_2 = (position_top_left.z() - position_bot_left.z())
              / (position_top_left.x() - position_bot_left.x());
    // calculate the first constant this is for the equation
    // involving the top left and top right point (initially)
    c_1 = - m_1 * position_top_left.x()
          + position_top_left.z();
    // calculate the second constant this is for the equation
    // involving the bot left and bot right point (initially)
    c_2 = - m_1 * position_bot_right.x()
          + position_bot_right.z();

    // calculate the third constant, this is for the
    // initially vertical lines
    c_3 = - m_2 * position_top_left.x()
          + position_top_left.z();
    // calculate the fourth constant, this is for the
    // initially vertical lines
    c_4 = - m_2 * position_bot_right.x()
          + position_bot_right.z();

    // calculate all the straigth line equations
    z_1 = c_1 + m_1 * intersection_point.x();
    z_2 = c_2 + m_1 * intersection_point.x();
    z_3 = c_3 + m_2 * intersection_point.x();
    z_4 = c_4 + m_2 * intersection_point.x();

    // order the previously calculated z values
    float largest_one = z_1 > z_2 ? z_1 : z_2,
        smallest_one = z_1 < z_2 ? z_1 : z_2,
        largest_two = z_3 > z_4 ? z_3 : z_4,
        smallest_two = z_3 < z_4 ? z_3 : z_4;

    // check if the point is within the plane
    if ( (largest_one >  intersection_point.z()) &&
         (smallest_one < intersection_point.z()) &&
         (largest_two >  intersection_point.z()) &&
         (smallest_two < intersection_point.z()) &&
         (round(position.y()) == round(intersection_point.y())) ) {
      return true;
    }
  }
  if ( no_rotation ) {
    if ( ( position.x() + scale.x() / 2.0 > intersection_point.x() ) &&
         ( position.x() - scale.x() / 2.0 < intersection_point.x() ) &&
         ( position.z() + scale.z() / 2.0 > intersection_point.z() ) &&
         ( position.z() - scale.z() / 2.0 < intersection_point.z() ) &&
         ( round(position.y()) == round(intersection_point.y()) ) ) {
      // check non rotated collision
      return true;
    }
  }
  return false;
}

bool Mathematics::detect_point_near_line(QVector3D point_a,
                                         QVector3D point_b,
                                         QVector3D position,
                                         float threshhold) {
  // this is to enable alternative (exeption) calculation when division by zero will happen
  bool vertical = false;
  float m, c, z;
  m = (round(point_a.x() - point_b.x()) != 0) ?
        (point_a.z() - point_b.z())/(point_a.x() - point_b.x()) :
        9999999.0;
  if(m > 999999.0) {
    vertical = true;
  } else {
    c = point_a.z() - m * point_a.x();
    z = m * position.x() + c;
    // qDebug() << z << position.z();
    float large_x = point_a.x() > point_b.x() ? point_a.x() : point_b.x();
    float small_x = point_a.x() < point_b.x() ? point_a.x() : point_b.x();
    if ( abs(z - position.z()) < threshhold &&
         large_x > position.x() &&
         small_x < position.x() ) {
      if ( abs(( position.y() - point_a.y() < threshhold )) ||
           abs(( position.y() - point_b.y() < threshhold )) )
        return true;
    }
  }
  // for vertical case
  if ( vertical ) {
    if ( abs(position.x() - point_a.x() ) < threshhold ) {
      float top = point_a.z() > point_b.z() ? point_a.z() : point_b.z(),
          bottom = point_a.z() < point_b.z() ? point_a.z() : point_b.z();
      if ( position.z() > bottom &&
           position.z() < top) {
        if ( abs(( position.y() - point_a.y() < threshhold )) ||
             abs(( position.y() - point_b.y() < threshhold )) )
          return true;
      }
    }
  }
  return false;
}

Mathematics::~Mathematics() {
}

