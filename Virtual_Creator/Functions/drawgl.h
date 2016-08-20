/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_FUNCTIONS_DRAWGL_H_
#define VIRTUAL_CREATOR_FUNCTIONS_DRAWGL_H_

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QVector3D>
#include <QtMath>
#include "Objects/ModelMesh.h"

class DrawGL {
public:
  DrawGL();
  ~DrawGL();
  static void DrawModel(ModelMesh*,
                        QMatrix4x4,
                        QMatrix4x4,
                        QMatrix4x4,
                        QOpenGLTexture*,
                        QVector3D,
                        QVector2D,
                        QOpenGLShaderProgram*,
                        QMatrix4x4, float);

  static void DrawLine(QVector3D,
                       QVector3D,
                       QMatrix4x4,
                       QMatrix4x4,
                       QMatrix4x4,
                       QVector3D,
                       QOpenGLShaderProgram*,
                       QMatrix4x4, float);

  static void ShaderDraw(ModelMesh*,
                         QOpenGLShaderProgram*);

  static void UpdateShaders(QMatrix4x4,
                            QMatrix4x4,
                            QMatrix4x4,
                            QOpenGLTexture*,
                            QVector3D,
                            QVector2D,
                            QOpenGLShaderProgram*,
                            QMatrix4x4, float);

  static void UpdateShaders(QMatrix4x4,
                            QMatrix4x4,
                            QMatrix4x4,
                            QVector3D,
                            QVector2D,
                            QOpenGLShaderProgram*,
                            QMatrix4x4, float);

  static void draw_if_true(ModelMesh*,
                           QMatrix4x4,
                           QVector3D,
                           QVector3D,
                           QVector3D,
                           QOpenGLTexture*,
                           QVector3D,
                           QVector2D,
                           QMatrix4x4,
                           QOpenGLShaderProgram*,
                           bool, float);
  static void setup_frame();
};

#endif  // VIRTUAL_CREATOR_FUNCTIONS_DRAWGL_H_
