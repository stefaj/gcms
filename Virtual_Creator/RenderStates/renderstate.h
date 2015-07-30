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
#include <QLabel>
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
    QOpenGLShaderProgram *program;
    QVector3D *position, *clicked_position;
    QVector<QOpenGLTexture *> textures;
    QVector<Node *> nodes;
    QVector<VisualObject *> models;
    QVector<QString> texture_paths;
    ModelMesh *node, *plane, *wall, *door, *tree;

    // internal integers used for mousemovement, counters etc.
    int mouse_x, mouse_y, dmouse_x, dmouse_y, node_index_selected;
    float mouse_zoom ,noderadius, mouse_y_inverted, current_floor_height;
    // define a view matrix
    QMatrix4x4 vMatrix;
    QVector3D *current_position;
    QVector3D position_camera, camera_prev, raycast, rotation, currentscale, drag_middle_position,
    corner_1, corner_2, corner_3, corner_4, center_h_1, center_h_2;
    bool mousedown_right, mousedown_left, node_placable,
    node_removable, tree_removable, node_linkable, pavement_placable,
    door_placeable, wall_placable, tree_placable, placable_floor_plan,
    node_significant;
    QString floor_plan_path, next_node_name;
    QVector<QOpenGLTexture *> textures_from_files;
    void add_pavement(QVector3D, QVector3D, QVector3D);
    void add_door(QVector3D, QVector3D, QVector3D);
    void add_wall(QVector3D, QVector3D, QVector3D);
    void add_tree(QVector3D, QVector3D, QVector3D);
    void add_floor_plan(QVector3D, QVector3D, QVector3D);
    void draw_circle_flat(QVector3D, QMatrix4x4,QVector3D, float);
    void LoadObjects(QString);
    void LoadTextures(QString);
    void LoadNodes(QString);
    const float tree_radius, infinte_lenght_lines;
    QLabel selected_label;
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
