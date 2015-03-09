/** *********************************************************************** **/
/** *********************************************************************** **/
/**     Created by:     Ruan (Baggins) Luies 23511354                       **/
/**     email:          23511354@nwu.ac.za                                  **/
/**     Project name:   Virtual Concierge Creator And Management System     **/
/**     File Name:      RenderState.h                                       **/
/**     From Date:      2015/02/24                                          **/
/**     To Date:        2015/10/01                                          **/
/** **********************************************************************  **/
/** *********************************************************************** **/
#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "VCCMObjects/ModelMesh.h"
#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>
#include <QGLWidget>
#include <QtOpenGL>
#include "VCCMObjects/NodeHandler.h"

class QGLContext;

class RenderState : public QObject, protected QOpenGLFunctions
{
     Q_OBJECT
public:
    RenderState();
    ~RenderState();
    ModelMesh *box,
              *sky,
              *wagen,
              *node;
    void setT(qreal t) { m_t = t; }
    void setForward(qreal forward){m_position->setX(forward+m_position->x());}
    void setViewportSize(const QSize &size) { m_viewportSize = size; }
public slots:
    void paint();
    void forwardmove();
private:
    // Reuse shaderprogram for all child classes
    //QGLShaderProgram *shaderProgram;// Cannot be parameter of a function (violation)
    // Projection for all child classes
    QMatrix4x4 pMatrix; // dynamic memory control not needed
    void DrawModel(ModelMesh *box, QMatrix4x4 wvp, QMatrix4x4 mvp, QMatrix4x4 rotate/*, GLuint texture*/, QVector3D color);
    void DrawLine(QVector3D point1, QVector3D point2,QMatrix4x4 wvp,QMatrix4x4 mvp, QMatrix4x4 rotate/*, GLuint texture*/,QVector3D color);
    void ShaderDraw(ModelMesh *box);
    void UpdateShaders(QMatrix4x4 wvp,QMatrix4x4 mvp, QMatrix4x4 rotate/*, GLuint texture*/, QVector3D color);
    void LoadContent();
    QSize m_viewportSize;
    QOpenGLShaderProgram *m_program;
    qreal m_t;
    QVector3D *m_position;
    NodeHandler *m_handler;
};

#endif // RENDERENGINE_H
