#ifndef VIRTUALCONCIERGERENDERSTATE_H
#define VIRTUALCONCIERGERENDERSTATE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include "Objects/ModelMesh.h"
#include "Objects/NodeHandler.h"
#include "Functions/drawgl.h"

class VirtualConciergeRenderstate : public QOpenGLWidget, protected QOpenGLFunctions
{
     Q_OBJECT
public:
    explicit VirtualConciergeRenderstate(QWidget *parent = 0);
    ~VirtualConciergeRenderstate();
private:
    ModelMesh *m_node;
    QMatrix4x4 pMatrix; // dynamic memory control not needed
    void LoadContent();
    QSize m_viewportSize;
    QOpenGLShaderProgram *m_program;
    QVector3D *m_position;
    NodeHandler *m_handler;
    QVector<QOpenGLTexture *> m_textures;
protected:
    void initializeGL();
   // void resizeGL(int w, int h);
    void paintGL();
    void resizeGL(int w, int h);
//    void mouseMoveEvent(QMouseEvent *);
//    void mousePressEvent(QMouseEvent *);
//    void wheelEvent(QWheelEvent *);
//    void mouseReleaseEvent(QMouseEvent *);
};

#endif // VIRTUALCONCIERGERENDERSTATE_H