#include "virtualconciergerenderstate.h"

VirtualConciergeRenderstate::VirtualConciergeRenderstate(QWidget *parent): QOpenGLWidget(parent),m_program(0){
    // enable antialiasing (set the format of the widget)
    QSurfaceFormat format;
    format.setSamples(4);
    this->setFormat(format);
    // clear the textures
    m_textures.clear();

    m_position = new QVector3D(0,0,0);
    m_handler = new NodeHandler();
    m_handler->ReadFilePVC("VirtualConcierge/nodes.pvc");
    //m_handler->CalculateShortest(0,1);


}

void VirtualConciergeRenderstate::LoadContent()
{
    // this initializes all the opengl functions
    initializeOpenGLFunctions();
    //load meshes
    m_node = new ModelMesh("://Sphere");
    // load shaders
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,":/Vertex");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,":/Fragment");
    m_program->link();

}

void VirtualConciergeRenderstate::initializeGL()
{
    // this initializes all the opengl functions
    initializeOpenGLFunctions();
    // texture test
    QOpenGLTexture *texture = new QOpenGLTexture(QImage("://Texture0").mirrored());
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_textures.append(texture);
}

void VirtualConciergeRenderstate::resizeGL(int w, int h){
    // setup the viewport for opengl
    glViewport(0, 0, w, h);

    // initialize the projection matrix
    pMatrix.setToIdentity();

    // set the projection matrix
    pMatrix.perspective(45, (float) w / (float) h, 1.0f, 1000.0f);
}

void VirtualConciergeRenderstate::paintGL(){
    // define a view matrix
       QMatrix4x4 vMatrix;
       // whenever content is not loaded, load the content
       if(!m_program){LoadContent();}
       glDepthMask(GL_TRUE);
       // clear the depth z = 0.0f -> 1.0f
       glClearDepth(1.0f);
       // enable the scene's depth test
       glEnable(GL_DEPTH_TEST);
       // enable cullmode CCW (counter clockwise)
       glEnable(GL_CULL_FACE);
       // clear the background color for rendering
       glClearColor(0.97f,0.97f,0.97f, 1);
       // clear the color and depth buffer
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       // setup camera
       QMatrix4x4 cameraTransformation;
       // rotation in the y - axis
       cameraTransformation.rotate(0, 0, 1, 0);
       // rotation in the x - axis
       cameraTransformation.rotate(-90, 1, 0, 0);
       // transform the camera's position with respect to the rotation matrix
       QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, 50.0) ;
       // define the direction of the camera's up vector
       QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);
       // implement and transform the camera
       vMatrix.lookAt(cameraPosition, QVector3D(), cameraUpDirection);
      // vMatrix.translate(m_camera_prev);

       // draw each node to the scene
       for(int x = 0; x<m_handler->count();x++)
       {
         // this is for the model transformation
         QMatrix4x4 mMatrix;
         // transform the position locally
         mMatrix.translate(m_handler->NodeFromIndex(x).Position());
         /*mMatrix.scale(4.0);*/
         // draw different types of nodes, (connected & unconnected nodes & best path)
         DrawGL::DrawModel(m_node,vMatrix,mMatrix,QMatrix4x4(),m_textures.value(0),m_handler->NodeFromIndex(x).getColor(),QVector2D(1,1),m_program,pMatrix);
       }
       for(int o = 0;o<m_handler->pathcount()-1;o++)
           DrawGL::DrawLine(m_handler->NodeFromIndex(m_handler->pathindex(o)).Position(),m_handler->NodeFromIndex(m_handler->pathindex(o+1)).Position(),
                vMatrix,QMatrix4x4(),QMatrix4x4(),QVector3D(0,1,0),m_program,pMatrix);

       // draw each node to the scene
       for(int z = 0; z<m_handler->count();z++)
       {
         for(int l = 0;l<m_handler->NodeFromIndex(z).countConnected();l++)
           DrawGL::DrawLine(m_handler->NodeFromIndex(z).Position(),m_handler->NodeFromIndex(m_handler->NodeFromIndex(z).getConnectedIndex(l)).Position(),
                  vMatrix,QMatrix4x4(),QMatrix4x4(),QVector3D(0,0,0),m_program,pMatrix);
       }
       //DrawModel(m_plane, vMatrix, QMatrix4x4(),QMatrix4x4(),QVector3D(0,0,0));
       // release the program for this frame
       m_program->release();
       // disable the cullmode for the frame
       glDisable(GL_CULL_FACE);
       // disable the depthtest for the frame
       glDisable(GL_DEPTH_TEST);
       // finish up the opengl frame
       glFinish();
}

VirtualConciergeRenderstate::~VirtualConciergeRenderstate(){
    delete m_program;
}

