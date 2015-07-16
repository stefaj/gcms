#ifndef VIRTUALCONCIERGERENDERSTATE_H
#define VIRTUALCONCIERGERENDERSTATE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include "Objects/ModelMesh.h"
#include "Objects/NodeHandler.h"

class VirtualConciergeRenderstate : public QOpenGLWidget, protected QOpenGLFunctions
{
     Q_OBJECT
public:
    explicit VirtualConciergeRenderstate(QWidget *parent = 0);
    ~VirtualConciergeRenderstate();
private:
    ModelMesh *m_node;
    QMatrix4x4 pMatrix; // dynamic memory control not needed
    void DrawModel(ModelMesh *box, QMatrix4x4 wvp, QMatrix4x4 mvp, QMatrix4x4 rotate/*, GLuint texture*/, QVector3D color);
    void DrawLine(QVector3D point1, QVector3D point2,QMatrix4x4 wvp,QMatrix4x4 mvp, QMatrix4x4 rotate/*, GLuint texture*/,QVector3D color);
    void ShaderDraw(ModelMesh *box);
    void UpdateShaders(QMatrix4x4 wvp,QMatrix4x4 mvp, QMatrix4x4 rotate/*, GLuint texture*/, QVector3D color);
    void LoadContent();
    QSize m_viewportSize;
    QOpenGLShaderProgram *m_program;
    QVector3D *m_position;
    NodeHandler *m_handler;
    QVector<QOpenGLTexture *> m_textures;
protected:
   // void initializeGL();
   // void resizeGL(int w, int h);
    void paintGL();
//    void mouseMoveEvent(QMouseEvent *);
//    void mousePressEvent(QMouseEvent *);
//    void wheelEvent(QWheelEvent *);
//    void mouseReleaseEvent(QMouseEvent *);
};

#endif // VIRTUALCONCIERGERENDERSTATE_H
