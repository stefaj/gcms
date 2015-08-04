/* Copyright 2015 Ruan Luies */

#include "./drawgl.h"

DrawGL::DrawGL() {
}

void DrawGL::UpdateShaders(QMatrix4x4 wvp,
                           QMatrix4x4 mvp,
                           QMatrix4x4 rotate,
                           QOpenGLTexture* texture,
                           QVector3D color,
                           QVector2D texturecooredinates,
                           QOpenGLShaderProgram* shader_program,
                           QMatrix4x4 pmatrix, float height) {
    // bind the current shader code
    shader_program->bind();
    // bind the texture for the object
    texture->bind();
    // update the y-clipping
    shader_program->setUniformValue("y_clipping", height);
    // update the colour of the object
    shader_program->setUniformValue("col", color);
    // change the rotation of the object in the shader
    shader_program->setUniformValue("rotationMatrix", rotate);
    // update model view projection
    shader_program->setUniformValue("mvpMatrix", mvp * rotate);
    // update world view projection in the shader
    shader_program->setUniformValue("wvpMatrix", pmatrix * wvp);
    // use GL_TEXTURE0
    shader_program->setUniformValue("texture", 0);
    // set the varying texture coordinate
    shader_program->setUniformValue("texture_coordinates",
                                    texturecooredinates);
}

void DrawGL::UpdateShaders(QMatrix4x4 wvp,
                           QMatrix4x4 mvp,
                           QMatrix4x4 rotate,
                           QVector3D color,
                           QVector2D texturecooredinates,
                           QOpenGLShaderProgram *shader_program,
                           QMatrix4x4 pmatrix, float height) {
    // bind the current shader code
    shader_program->bind();
    // update the y-clipping
    shader_program->setUniformValue("y_clipping", height);
    // update the colour of the object
    shader_program->setUniformValue("col", color);
    // change the rotation of the object in the shader
    shader_program->setUniformValue("rotationMatrix", rotate);
    // update model view projection
    shader_program->setUniformValue("mvpMatrix", mvp * rotate);
    // update world view projection in the shader
    shader_program->setUniformValue("wvpMatrix", pmatrix * wvp);
    // use GL_TEXTURE0
    shader_program->setUniformValue("texture", 0);
    // set the varying texture coordinate
    shader_program->setUniformValue("texture_coordinates",
                                    texturecooredinates);
}

void DrawGL::ShaderDraw(ModelMesh* box,
                        QOpenGLShaderProgram* shader_program) {
  if ( (box == (void*)0x1) || (box == (void*)0x0) ||
       (shader_program == (void*)0x1) ||
       (shader_program == (void*)0x0)) {
      return;
  }
  // load the vertices to the shaders
  shader_program->setAttributeArray("vertex", box->vertices.constData());
  // enable the shader attribute( vertices )
  shader_program->enableAttributeArray("vertex");
  // load the normals to the shaders
  shader_program->setAttributeArray("normal", box->normals.constData());
  // enable the shader attribute( normals )
  shader_program->enableAttributeArray("normal");
  // load the texture coordinates to the shaders
  shader_program->setAttributeArray("textureCoordinate",
                                    box->textureCoordinates.constData());
  // enable the texture attribute
  shader_program->enableAttributeArray("textureCoordinate");
    // draw the opengl vertices
  box->Draw();
  // disable the vertex attributes
  shader_program->disableAttributeArray("vertex");
  // disable the normal attributes
  shader_program->disableAttributeArray("normal");
  // disable the Texture coordinates attributes
  shader_program->disableAttributeArray("textureCoordinate");
  // release the current updated shader code (awaiting next frame)
  shader_program->release();
}


void DrawGL::DrawLine(QVector3D point1,
                      QVector3D point2,
                      QMatrix4x4 wvp,
                      QMatrix4x4 mvp,
                      QMatrix4x4 rotate,
                      QVector3D color,
                      QOpenGLShaderProgram* shader_program,
                      QMatrix4x4 pmatrix, float height) {
    QVector< QVector3D > temp_vertices;
    temp_vertices.push_back(point1);
    temp_vertices.push_back(point2);
    UpdateShaders(wvp,
                  mvp,
                  rotate,
                  color,
                  QVector2D(1, 1),
                  shader_program,
                  pmatrix, height);
    // load the vertices to the shaders
    shader_program->setAttributeArray("vertex", temp_vertices.constData());
    // enable the shader attribute( vertices )
    shader_program->enableAttributeArray("vertex");
    // load the normals to the shaders
    shader_program->setAttributeArray("normal", temp_vertices.constData());
    // enable the shader attribute( vertices )
    shader_program->enableAttributeArray("normal");
    glLineWidth(2.5);
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    glDrawArrays(GL_LINES, 0, temp_vertices.size());
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // disable the vertex attributes
    shader_program->disableAttributeArray("vertex");
    // disable the normal attributes
    shader_program->disableAttributeArray("normal");
    // release the current updated shader code (awaiting next frame)
    shader_program->release();
    temp_vertices.clear();
}

void DrawGL::DrawModel(ModelMesh *box,
                       QMatrix4x4 wvp,
                       QMatrix4x4 mvp,
                       QMatrix4x4 rotate,
                       QOpenGLTexture* texture,
                       QVector3D color,
                       QVector2D texturecoordmulti,
                       QOpenGLShaderProgram* shader_program,
                       QMatrix4x4 pmatrix, float height) {
     UpdateShaders(wvp,
                   mvp,
                   rotate,
                   texture,
                   color,
                   texturecoordmulti,
                   shader_program,
                   pmatrix, height);
     ShaderDraw(box,
                shader_program);
}

void DrawGL::draw_if_true(ModelMesh *model,
                          QMatrix4x4 view,
                          QVector3D position,
                          QVector3D rotation,
                          QVector3D scaling,
                          QOpenGLTexture* texture,
                          QVector3D color,
                          QVector2D texturecoord,
                          QMatrix4x4 pmatrix,
                          QOpenGLShaderProgram* shader_program,
                          bool value, float height) {
    if ( value ) {
        QMatrix4x4 translation;
        translation.translate(position);
        QMatrix4x4 rotationmat;
        rotationmat.rotate(rotation.y(), 0, 1, 0);
        rotationmat.scale(scaling);
        DrawGL::DrawModel(model,
                          view,
                          translation,
                          rotationmat,
                          texture,
                          color,
                          texturecoord,
                          shader_program,
                          pmatrix, height);
    }
}

DrawGL::~DrawGL() {
}

