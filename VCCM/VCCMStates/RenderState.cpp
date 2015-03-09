/** *********************************************************************** **/
/** *********************************************************************** **/
/**     Created by:     Ruan (Baggins) Luies 23511354                       **/
/**     email:          23511354@nwu.ac.za                                  **/
/**     Project name:   Virtual Concierge Creator And Management System     **/
/**     File Name:      RenderState.cpp                                     **/
/**     From Date:      2015/02/24                                          **/
/**     To Date:        2015/10/01                                          **/
/** **********************************************************************  **/
/** *********************************************************************** **/

#include "VCCMStates/RenderState.h"
#include <qdebug.h>

RenderState::RenderState(): m_program(0), m_t(0) {
    m_position = new QVector3D(0,0,0);
    m_handler = new NodeHandler();

    m_handler->AddNode(new Node(new QVector3D(0,0,0),new QString("Node 1")));
    m_handler->AddNode(new Node(new QVector3D(5,0,5),new QString("Node 2")));
    m_handler->AddNode(new Node(new QVector3D(-5,0,-5),new QString("Node 3")));

    m_handler->AddNodeLink(0,new QString("Node 2"));
m_handler->AddNodeLink(1,new QString("Node 1"));
     for(int l = 0; l< m_handler->NodeFromIndex(0).countConnected();l++)
           qDebug()<< m_handler->NodeFromIndex(0).getLinkedName(l);
}

void RenderState::paint()
{
    glDepthMask(GL_TRUE);
    glClearDepth(1.0f);

    if(!m_program){LoadContent();}
    m_program->setUniformValue("t", (float) m_t);
    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    pMatrix.setToIdentity();
    pMatrix.perspective(60, (float) m_viewportSize.width() / (float) m_viewportSize.height(), 1.0f, 1000.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.97, 0.97, 0.97, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 vMatrix;

    // camera
    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(0, 0, 1, 0);
    cameraTransformation.rotate(-90, 1, 0, 0);
    QVector3D cameraPosition = cameraTransformation * QVector3D(m_position->x(), 0, 16.5);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);
    vMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);

DrawLine(QVector3D(0,0,0),QVector3D(5,0,5),vMatrix,QMatrix4x4(),QMatrix4x4(),QVector3D(0,0,0));
DrawLine(QVector3D(0,0,0),QVector3D(-5,0,-5),vMatrix,QMatrix4x4(),QMatrix4x4(),QVector3D(0,0,0));
    for(int x = 0; x<m_handler->count();x++)
    {
      QMatrix4x4 mMatrix;
      mMatrix.translate(m_handler->NodeFromIndex(x).Position());

      if(m_handler->NodeFromIndex(x).countConnected() >0)
      DrawModel(node,vMatrix,mMatrix,QMatrix4x4()/*,0*/,QVector3D(0,1,0));
      else
          DrawModel(node,vMatrix,mMatrix,QMatrix4x4()/*,0*/,QVector3D(1,0,0));
    }
    m_program->release();

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glFinish();
}

void RenderState::LoadContent()
{
    initializeOpenGLFunctions();
    //load meshes
    box = new ModelMesh(":/block");
    node = new ModelMesh(":/Node");
    sky= new ModelMesh(":/Sky");
    wagen = new ModelMesh(":/Cube");
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,":/VertexShader");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,":/FragmentShader");
    m_program->link();
}

void RenderState::UpdateShaders(QMatrix4x4 wvp,QMatrix4x4 mvp, QMatrix4x4 rotate/*, GLuint texture*/,QVector3D color)
{
    //glBindTexture(GL_TEXTURE_2D, texture);
    m_program->bind();// bind the current shader code
    m_program->setUniformValue("col",color);
    m_program->setUniformValue("rotationMatrix", rotate);
    m_program->setUniformValue("mvpMatrix", mvp * rotate);// model view projection
    m_program->setUniformValue("wvpMatrix", pMatrix * wvp);// model view projection
    //shaderProgram->setUniformValue("texture", 0);// use GL_TEXTURE0
}

void RenderState::ShaderDraw(ModelMesh *box)
{

    const char *vert ="vertex";//= vertex.toStdString().c_str();// convert the qstring to c-string for opengl purposes
    //const char *textureCoordinate= "textureCoordinate";//= texCoord.toStdString().c_str();// convert the qstring to c-string for opengl purposes
    const char *normals = "normal";// convert the qstring to c-string for opengl purposes
    m_program->setAttributeArray(vert, box->vertices.constData());//load the vertices to the shaders
    m_program->enableAttributeArray(vert);//enable the shader attribute( vertices )
    m_program->setAttributeArray(normals, box->normals.constData());//load the normals to the shaders
    m_program->enableAttributeArray(normals);//enable the shader attribute( normals )
       //m_program->setAttributeArray(textureCoordinate, box->textureCoordinates.constData());//load the texture coordinates to the shaders
      // m_program->enableAttributeArray(textureCoordinate);//enable the shader attribute( texture coordinates )
       box->Draw(); // draw the opengl vertices
       m_program->disableAttributeArray(vert);// disable the vertex attributes
       m_program->disableAttributeArray(normals);// disable the normal attributes
       //m_program->disableAttributeArray(textureCoordinate);// disable the Texture coordinates attributes

       m_program->release(); // release the current updated shader code (awaiting next frame)
   }
   void RenderState::DrawLine(QVector3D point1, QVector3D point2,QMatrix4x4 wvp,QMatrix4x4 mvp, QMatrix4x4 rotate/*, GLuint texture*/,QVector3D color)
   {
       QVector< QVector3D > temp_vertices;
       temp_vertices.push_back(point1);
       temp_vertices.push_back(point2);
   UpdateShaders(wvp, mvp, rotate/*, texture*/, color);
    const char *vert ="vertex";//= vertex.toStdString().c_str();// convert the qstring to c-string for opengl purposes
    //const char *textureCoordinate= "textureCoordinate";//= texCoord.toStdString().c_str();// convert the qstring to c-string for opengl purposes
    const char *normals = "normal";// convert the qstring to c-string for opengl purposes
    m_program->setAttributeArray(vert, temp_vertices.constData());//load the vertices to the shaders
    m_program->enableAttributeArray(vert);//enable the shader attribute( vertices )
    m_program->setAttributeArray(normals, temp_vertices.constData());//load the normals to the shaders
    m_program->enableAttributeArray(normals);//enable the shader attribute( vertices )
    //m_program->setAttributeArray(textureCoordinate, box->textureCoordinates.constData());//load the texture coordinates to the shaders
   // m_program->enableAttributeArray(textureCoordinate);//enable the shader attribute( texture coordinates )
    glLineWidth(2.0);
    glDrawArrays(GL_LINES, 0, temp_vertices.size());

    m_program->disableAttributeArray(vert);// disable the vertex attributes
    m_program->disableAttributeArray(normals);// disable the normal attributes
    m_program->release(); // release the current updated shader code (awaiting next frame)
    temp_vertices.clear();
}
void RenderState::DrawModel(ModelMesh *box,QMatrix4x4 wvp,QMatrix4x4 mvp, QMatrix4x4 rotate/*, GLuint texture*/,QVector3D color)
 {
     UpdateShaders(wvp, mvp, rotate/*, texture*/, color);
     ShaderDraw(box);
 }

void RenderState::forwardmove()
{
    m_position->setX(m_position->x()+0.1f);
}

RenderState::~RenderState()
{
    delete m_program;
}
