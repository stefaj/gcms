#ifndef DRAWGL_H
#define DRAWGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QVector3D>
#include <QtMath>
#include "Objects/ModelMesh.h"

class DrawGL
{
public:
    DrawGL();
    ~DrawGL();
    static void DrawModel(ModelMesh *, QMatrix4x4 , QMatrix4x4 , QMatrix4x4 ,QOpenGLTexture *, QVector3D , QVector2D,QOpenGLShaderProgram*, QMatrix4x4);
    static void DrawLine(QVector3D , QVector3D ,QMatrix4x4 ,QMatrix4x4 , QMatrix4x4 /*, GLuint texture*/,QVector3D ,QOpenGLShaderProgram*, QMatrix4x4);
    static void ShaderDraw(ModelMesh *,QOpenGLShaderProgram*);
    static void UpdateShaders(QMatrix4x4 ,QMatrix4x4 , QMatrix4x4 ,QOpenGLTexture *, QVector3D, QVector2D,QOpenGLShaderProgram*, QMatrix4x4);
    static void UpdateShaders(QMatrix4x4 ,QMatrix4x4 , QMatrix4x4 , QVector3D, QVector2D,QOpenGLShaderProgram*, QMatrix4x4);

};

#endif // DRAWGL_H
