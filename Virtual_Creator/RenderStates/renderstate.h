/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_RENDERSTATES_RENDERSTATE_H_
#define VIRTUAL_CREATOR_RENDERSTATES_RENDERSTATE_H_

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
#include <QPainter>
#include "Objects/ModelMesh.h"
#include "Objects/Node.h"
#include "Objects/visualobject.h"
#include "Functions/premises_exporter.h"
#include "Functions/drawgl.h"

class RenderState : public QOpenGLWidget, protected QOpenGLFunctions {
     Q_OBJECT

 public:
    explicit RenderState(QWidget *parent = 0);
    ~RenderState();

 protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

 private:
    QMatrix4x4 pMatrix, vMatrix;
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
    float mouse_zoom, noderadius, mouse_y_inverted, current_floor_height;
    QVector3D *current_position;
    QVector3D position_camera,
            camera_prev,
            raycast,
            rotation,
            currentscale,
            drag_middle_position,
            corner_1,
            corner_2,
            corner_3,
            corner_4,
            center_h_1,
            center_h_2;
    bool mousedown_right, mousedown_left, node_placable,
    node_removable, tree_removable, node_linkable, pavement_placable,
    door_placeable, wall_placable, tree_placable, placable_floor_plan,
    node_significant, floor_plan_removable, link_removable, start_up_load_tex;
    QString floor_plan_path, next_node_name;
    QVector<QOpenGLTexture *> textures_from_files;
    void add_pavement(QVector3D rotation,
                      QVector3D position,
                      QVector3D scale);
    void add_door(QVector3D rotation,
                  QVector3D position,
                  QVector3D scale);
    void add_wall(QVector3D rotation,
                  QVector3D position,
                  QVector3D scale);
    void add_tree(QVector3D rotation,
                  QVector3D position,
                  QVector3D scale);
    void add_floor_plan(QVector3D rotation,
                        QVector3D position,
                        QVector3D scale);
    void draw_circle_flat(QVector3D position,
                          QMatrix4x4 view_matrix,
                          QVector3D color,
                          float radius);
    void LoadObjects(QString filename);
    void LoadTextures(QString filename);
    void LoadNodes(QString filename);
    void CopyDirectories(QString filename);
    void RemoveNodes();
    void DrawNodes();
    void DrawNodeNames();
    void DrawNodeLines(QVector3D Pos);
    void DrawPlacableItems(QVector3D Pos);
    void DrawObjectLines(QVector3D Pos);
    void remove_floorplan();
    void remove_link();
    const float tree_radius, infinte_lenght_lines;
    QLabel selected_label;

 private slots:
    void add_node(QString* name);
    void allow_node(bool allow);
    void allow_remove_node(bool allow);
    void allow_remove_tree(bool allow);
    void allow_link(bool allow);
    void allow_pavement(bool allow);
    void allow_door(bool allow);
    void allow_wall(bool allow);
    void allow_tree(bool allow);
    void allow_floor_plan(bool allow);
    void change_rotY(double degrees);
    void invert_mouseY(bool invert_mouse);
    void load_texture_from_file(QString filename);
    void set_object_scale(QVector3D scale);
    void change_current_floor_height(float y_height);
    void set_next_node_name(QString name);
    void set_next_node_significant(bool is_significant);
    void load_premises(QString filename);
    void allow_remove_floor_plan(bool allow);
    void allow_remove_link(bool allow);

  signals:
    void opengl_initialised(bool);
};

#endif  // VIRTUAL_CREATOR_RENDERSTATES_RENDERSTATE_H_
