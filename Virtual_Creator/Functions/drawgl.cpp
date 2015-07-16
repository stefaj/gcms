#include "drawgl.h"

DrawGL::DrawGL()
{

}

void DrawGL::UpdateShaders(QMatrix4x4 wvp,QMatrix4x4 mvp, QMatrix4x4 rotate, QOpenGLTexture * texture,QVector3D color, QVector2D texturecooredinates, QOpenGLShaderProgram *m_program, QMatrix4x4 pmatrix){
    // bind the current shader code
    m_program->bind();
    // bind the texture for the object
    texture->bind();
    // update the colour of the object
    m_program->setUniformValue("col",color);
    // change the rotation of the object in the shader
    m_program->setUniformValue("rotationMatrix", rotate);
    // update model view projection
    m_program->setUniformValue("mvpMatrix", mvp * rotate);
    // update world view projection in the shader
    m_program->setUniformValue("wvpMatrix", pmatrix * wvp);
    // use GL_TEXTURE0
    m_program->setUniformValue("texture", 0);
    // set the varying texture coordinate
    m_program->setUniformValue("texture_coordinates",texturecooredinates);
}

void DrawGL::UpdateShaders(QMatrix4x4 wvp,QMatrix4x4 mvp, QMatrix4x4 rotate,QVector3D color, QVector2D texturecooredinates, QOpenGLShaderProgram *m_program, QMatrix4x4 pmatrix){
    // bind the current shader code
    m_program->bind();
    // update the colour of the object
    m_program->setUniformValue("col",color);
    // change the rotation of the object in the shader
    m_program->setUniformValue("rotationMatrix", rotate);
    // update model view projection
    m_program->setUniformValue("mvpMatrix", mvp * rotate);
    // update world view projection in the shader
    m_program->setUniformValue("wvpMatrix", pmatrix * wvp);
    // use GL_TEXTURE0
    m_program->setUniformValue("texture", 0);
    // set the varying texture coordinate
    m_program->setUniformValue("texture_coordinates",texturecooredinates);
}

void DrawGL::ShaderDraw(ModelMesh *box,QOpenGLShaderProgram *m_program){
    // load the vertices to the shaders
    m_program->setAttributeArray("vertex", box->m_vertices.constData());
    // enable the shader attribute( vertices )
    m_program->enableAttributeArray("vertex");
    // load the normals to the shaders
    m_program->setAttributeArray("normal", box->m_normals.constData());
    // enable the shader attribute( normals )
    m_program->enableAttributeArray("normal");
    // load the texture coordinates to the shaders
    m_program->setAttributeArray("textureCoordinate", box->m_textureCoordinates.constData());
    // enable the texture attribute
    m_program->enableAttributeArray("textureCoordinate");
    // draw the opengl vertices
    box->Draw();
    // disable the vertex attributes
    m_program->disableAttributeArray("vertex");
    // disable the normal attributes
    m_program->disableAttributeArray("normal");
    // disable the Texture coordinates attributes
    m_program->disableAttributeArray("textureCoordinate");
    // release the current updated shader code (awaiting next frame)
    m_program->release();
   }

void DrawGL::DrawLine(QVector3D point1, QVector3D point2,QMatrix4x4 wvp,QMatrix4x4 mvp, QMatrix4x4 rotate, QVector3D color,QOpenGLShaderProgram *m_program, QMatrix4x4 pmatrix){
    QVector< QVector3D > temp_vertices;
    temp_vertices.push_back(point1);
    temp_vertices.push_back(point2);
    UpdateShaders(wvp, mvp, rotate, color,QVector2D(1,1),m_program,pmatrix);
    m_program->setAttributeArray("vertex", temp_vertices.constData());//load the vertices to the shaders
    m_program->enableAttributeArray("vertex");//enable the shader attribute( vertices )
    m_program->setAttributeArray("normal", temp_vertices.constData());//load the normals to the shaders
    m_program->enableAttributeArray("normal");//enable the shader attribute( vertices )
    glLineWidth(2.0);
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
    glDrawArrays(GL_LINES, 0, temp_vertices.size());
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    m_program->disableAttributeArray("vertex");// disable the vertex attributes
    m_program->disableAttributeArray("normal");// disable the normal attributes
    m_program->release(); // release the current updated shader code (awaiting next frame)
    temp_vertices.clear();
}

void DrawGL::DrawModel(ModelMesh *box,QMatrix4x4 wvp,QMatrix4x4 mvp, QMatrix4x4 rotate,QOpenGLTexture *texture,QVector3D color,QVector2D texturecoordmulti,QOpenGLShaderProgram *m_program, QMatrix4x4 pmatrix){
     UpdateShaders(wvp, mvp, rotate,texture, color,texturecoordmulti,m_program,pmatrix);
     ShaderDraw(box,m_program);
}
DrawGL::~DrawGL()
{

}

