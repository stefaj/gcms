/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_RENDERSTATES_VIRTUALCONCIERGERENDERSTATE_H_
#define VIRTUAL_CREATOR_RENDERSTATES_VIRTUALCONCIERGERENDERSTATE_H_

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include "Objects/ModelMesh.h"
#include "Objects/NodeHandler.h"
#include "Functions/drawgl.h"
#include "Objects/visualobject.h"
#include "Functions/premises_exporter.h"

class VirtualConciergeRenderstate :
        public QOpenGLWidget,
        protected QOpenGLFunctions {
     Q_OBJECT

 public:
    explicit VirtualConciergeRenderstate(QWidget *parent = 0);
    ~VirtualConciergeRenderstate();

 private:
    void LoadContent();
    void LoadObjects(QString);
    void LoadTextures(QString);
    ModelMesh *node, *plane, *wall, *door, *tree;
    QMatrix4x4 pMatrix;
    QSize viewportSize;
    QOpenGLShaderProgram *program;
    QVector3D *position;
    NodeHandler *handler;
    QVector<QOpenGLTexture *> textures, textures_predefined;
    QVector<VisualObject *> objects;
    int start, end;
    QSurfaceFormat format;
    QTimer *frame_update;

 protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

 private slots:
    void find_path(int start, int end);
    void update_frame();
};

#endif  // VIRTUAL_CREATOR_RENDERSTATES_VIRTUALCONCIERGERENDERSTATE_H_
