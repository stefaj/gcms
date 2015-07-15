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
#include "Objects/ModelMesh.h"
#include "Objects/Node.h"
#include "visualobject.h"

class RenderState : public QOpenGLWidget, protected QOpenGLFunctions
{
     Q_OBJECT
public:
    explicit RenderState(QWidget *parent = 0);
    ~RenderState();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    // Reuse shaderprogram for all child classes
    // QGLShaderProgram *shaderProgram;// Cannot be parameter of a function (violation)
    // Projection for all child classes
    QMatrix4x4 pMatrix; // dynamic memory control not needed
    void DrawModel(ModelMesh *, QMatrix4x4 , QMatrix4x4 , QMatrix4x4 ,QOpenGLTexture *, QVector3D );
    void DrawLine(QVector3D , QVector3D ,QMatrix4x4 ,QMatrix4x4 , QMatrix4x4 /*, GLuint texture*/,QVector3D );
    void ShaderDraw(ModelMesh *);
    void UpdateShaders(QMatrix4x4 ,QMatrix4x4 , QMatrix4x4 ,QOpenGLTexture *, QVector3D );
    void LoadContent();
    QSize m_viewportSize;
    QOpenGLShaderProgram *m_program;
    QVector3D *m_position, *m_clicked_position;
    QVector<QOpenGLTexture *> m_textures;
    QVector<Node *> m_nodes;
    QVector<VisualObject *> m_models;
    ModelMesh *box, *sky, *wagen, *node, *m_plane, *m_wall, *m_door, *m_tree;
    int m_mouse_x, m_mouse_y, m_dmouse_x,m_dmouse_y,m_node_index_selected;
    float m_mouse_zoom,m_noderadius,m_mouse_y_inverted;
    // define a view matrix
    QMatrix4x4 vMatrix;
    QVector3D *m_current_position;
    QVector3D m_position_camera, m_camera_prev, m_raycast, m_rotation, m_currentscale, m_drag_middle_position,
    m_corner_1, m_corner_2, m_corner_3, m_corner_4, m_center_h_1, m_center_h_2;
    bool m_mousedown_right, m_mousedown_left, m_node_placable,
    m_node_removable, m_tree_removable, m_node_linkable, m_pavement_placable,
    m_door_placeable,m_wall_placable, m_tree_placable;
    void draw_if_true(ModelMesh*,QMatrix4x4, QVector3D, QVector3D, QVector3D,QOpenGLTexture *, QVector3D, bool);
    void add_pavement(QVector3D, QVector3D, QVector3D);
    void add_door(QVector3D, QVector3D, QVector3D);
    void add_wall(QVector3D, QVector3D, QVector3D);
    void add_tree(QVector3D, QVector3D, QVector3D);
    void draw_circle_flat(QVector3D, QMatrix4x4,QVector3D, float);
    const float tree_radius, infinte_lenght_lines;
    const char *vertex, *textureCoordinate, *normal;
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
    void change_rotY(double);
    void invert_mouseY(bool);
};

#endif // RENDERSTATE_H
