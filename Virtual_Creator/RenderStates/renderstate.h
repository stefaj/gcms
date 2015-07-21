#ifndef RENDERSTATE_H
#define RENDERSTATE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QVector3D>
#include <QTimer>
#include <QtMath>
#include <QMessageBox>
#include "Objects/ModelMesh.h"
#include "Objects/Node.h"
#include "Objects/visualobject.h"
#include "Functions/premises_exporter.h"
#include "Functions/drawgl.h"

class RenderState : public QOpenGLWidget, protected QOpenGLFunctions
{
     Q_OBJECT
public:
    explicit RenderState(QWidget *parent = 0);
    ~RenderState();
protected:
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    QMatrix4x4 pMatrix; // dynamic memory control not needed
    void LoadContent();
    QOpenGLShaderProgram *m_program;
    QVector3D *m_position, *m_clicked_position;
    QVector<QOpenGLTexture *> m_textures;
    QVector<Node *> m_nodes;
    QVector<VisualObject *> m_models;
    QVector<QString> m_texture_paths;
    ModelMesh *m_node, *m_plane, *m_wall, *m_door, *m_tree;

    // internal integers used for mousemovement, counters etc.
    int m_mouse_x, m_mouse_y, m_dmouse_x, m_dmouse_y, m_node_index_selected;
    float m_mouse_zoom ,m_noderadius, m_mouse_y_inverted, m_current_floor_height;
    // define a view matrix
    QMatrix4x4 vMatrix;
    QVector3D *m_current_position;
    QVector3D m_position_camera, m_camera_prev, m_raycast, m_rotation, m_currentscale, m_drag_middle_position,
    m_corner_1, m_corner_2, m_corner_3, m_corner_4, m_center_h_1, m_center_h_2;
    bool m_mousedown_right, m_mousedown_left, m_node_placable,
    m_node_removable, m_tree_removable, m_node_linkable, m_pavement_placable,
    m_door_placeable, m_wall_placable, m_tree_placable, m_placable_floor_plan,
    m_node_significant;
    QString m_floor_plan_path, m_next_node_name;
    QVector<QOpenGLTexture *> m_textures_from_files;
    void add_pavement(QVector3D, QVector3D, QVector3D);
    void add_door(QVector3D, QVector3D, QVector3D);
    void add_wall(QVector3D, QVector3D, QVector3D);
    void add_tree(QVector3D, QVector3D, QVector3D);
    void add_floor_plan(QVector3D, QVector3D, QVector3D);
    void draw_circle_flat(QVector3D, QMatrix4x4,QVector3D, float);
    void LoadObjects(QString);
    void LoadTextures(QString);
    const float tree_radius, infinte_lenght_lines;
private slots:
    void add_node(QString *);
    void allow_node(bool);
    void allow_remove_node(bool);
    void allow_remove_tree(bool);
    void allow_link(bool);
    void allow_pavement(bool);
    void allow_door(bool);
    void allow_wall(bool);
    void allow_tree(bool);
    void allow_floor_plan(bool);
    void change_rotY(double);
    void invert_mouseY(bool);
    void load_texture_from_file(QString);
    void set_object_scale(QVector3D);
    void change_current_floor_height(float);
    void set_next_node_name(QString);
    void set_next_node_significant(bool);
    void load_premises(QString);
};

#endif // RENDERSTATE_H
