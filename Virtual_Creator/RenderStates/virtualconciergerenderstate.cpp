#include "virtualconciergerenderstate.h"
#include <QFileDialog>

VirtualConciergeRenderstate::VirtualConciergeRenderstate(QWidget *parent): QOpenGLWidget(parent),m_program(0),m_start(0),m_end(0){
    // enable antialiasing (set the format of the widget)

    /*QSurfaceFormat format;
    format.setSwapBehavior(QSurfaceFormat::SingleBuffer);
    format.setSamples(4);
    this->setFormat(format);*/

    // clear the textures
    m_textures.clear();
    m_textures_predefined.clear();
    m_position = new QVector3D(0,0,0);
    m_handler = new NodeHandler();

    if(PremisesExporter::fileExists("VirtualConcierge/nodes.pvc"))
        m_handler->ReadFilePVC("VirtualConcierge/nodes.pvc");

    //m_handler->CalculateShortest(0,1);
    //find_path(0,5);
}

void VirtualConciergeRenderstate::find_path(int start, int end){
    if((m_handler->count()>start)&&(m_handler->count()>end))
        m_handler->CalculateShortest(start,end);

    // update the frame of the virtual concierge
    paintGL();
    update();
}

void VirtualConciergeRenderstate::LoadTextures(QString path){
    // clear the premises when not empty
    if(m_textures.count()>0)
        m_textures.clear();

    /* populate the textures from the text file */

    // load the text file
    QFile textfile(path);

    // open the text file
    textfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ascread(&textfile);

    if(textfile.isOpen()){
        // read each line of the file
        QString line = ascread.readLine();

        while(!line.isNull()){
            // break the line up in usable parts
            QStringList list = line.split(",");

            // check the type of line
            /* n-> node
             * j-> join
             */
            if(list[0]=="t"){

                int texture_index = 0;
                QString texture_path ="";

                // texture type
                QTextStream(&list[2])>>texture_path;

                // texture index
                QTextStream(&list[1])>>texture_index;

                // load texture
                QOpenGLTexture *texture = new QOpenGLTexture(QImage(texture_path).mirrored());
                texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
                texture->setMagnificationFilter(QOpenGLTexture::Linear);
                m_textures.push_back(texture);
            }

            // read next line
           line = ascread.readLine();
        }

        // close the textfile
        textfile.close();
    }
}

void VirtualConciergeRenderstate::LoadObjects(QString path){
    // clear the premises when not empty
    if(m_objects.count()>0)
        m_objects.clear();

    /* populate the premisis from the text file */

    // load the text file
    QFile textfile(path);

    // open the text file
    textfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ascread(&textfile);

    if(textfile.isOpen()){
        // read each line of the file
        QString line = ascread.readLine();

        while(!line.isNull()){
            // break the line up in usable parts
            QStringList list = line.split(",");

            // check the type of line
            /* n-> node
             * j-> join
             */
            if(list[0]=="o"){
                // this is only x,y,z coordinates for the node
                float matrix[9];
                int texture_index = 0;
                QString Type ="";

                // populate the vertices
                for(int i = 0;i<9;i++)
                     QTextStream(&list[i+3])>>matrix[i];

                // texture index
                QTextStream(&list[12])>>texture_index;

                // object type
                QTextStream(&list[2])>>Type;

                // add floorplan
                if(Type.compare("FloorPlan",Qt::CaseInsensitive)==0){
                    if(texture_index<m_textures.count()){
                        VisualObject *object = new VisualObject(m_plane,m_textures[texture_index],
                                                                QVector3D(matrix[0],matrix[1],matrix[2]),
                                                                QVector3D(matrix[3],matrix[4],matrix[5]),"FloorPlan");
                    object->setScaling(QVector3D(matrix[6],matrix[7],matrix[8]));
                    m_objects.push_back(object);
                    }
                }
            }

            // read next line
           line = ascread.readLine();
        }

        // close the textfile
        textfile.close();
    }
}

void VirtualConciergeRenderstate::LoadContent(){
    // this initializes all the opengl functions
    initializeOpenGLFunctions();
    //load meshes
    m_node = new ModelMesh(":/Sphere");
    m_plane = new ModelMesh(":/Plane");
    m_door = new ModelMesh("://DoorWay01");
    m_wall = new ModelMesh("://Wall01");
    m_tree = new ModelMesh("://Tree01");

    // load objects and textures
    if(PremisesExporter::fileExists("VirtualConcierge/textures.tl"))
        LoadTextures("VirtualConcierge/textures.tl");
    if(PremisesExporter::fileExists("VirtualConcierge/environment.env"))
        LoadObjects("VirtualConcierge/environment.env");
    // load shaders
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,":/Vertex");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,":/Fragment");
    m_program->link();

}

void VirtualConciergeRenderstate::initializeGL(){
    // this initializes all the opengl functions
    initializeOpenGLFunctions();
    // texture test
    QOpenGLTexture *texture = new QOpenGLTexture(QImage("://Texture0").mirrored());
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_textures_predefined.append(texture);
    glReadBuffer(GL_FRONT);

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
       QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, 80.0) ;
       // define the direction of the camera's up vector
       QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);
       // implement and transform the camera
       vMatrix.lookAt(cameraPosition, QVector3D(), cameraUpDirection);
       // draw other objects first
       foreach(VisualObject *object, m_objects){
           QMatrix4x4 translation;
           translation.translate(object->getTranslation());
           QMatrix4x4 rotation;
           rotation.rotate(object->getRotation().y(),0,1,0);
           rotation.scale(object->getScaling());
           if(object->getType().compare("FloorPlan")!=0)
           DrawGL::DrawModel(object->getModelMesh(), vMatrix, translation,rotation,object->getTexture(),QVector3D(),QVector2D(object->getScaling().z(),object->getScaling().x()),m_program,pMatrix);
           else
           DrawGL::DrawModel(object->getModelMesh(), vMatrix, translation,rotation,object->getTexture(),QVector3D(),QVector2D(1,1),m_program,pMatrix);
        }

//       // draw each node to the scene
//       for(int x = 0; x<m_handler->count();x++){
//         // this is for the model transformation
//         QMatrix4x4 mMatrix;
//         // transform the position locally
//         mMatrix.translate(m_handler->NodeFromIndex(x).Position());
//         // draw different types of nodes, (connected & unconnected nodes & best path)
//         DrawGL::DrawModel(m_node,vMatrix,mMatrix,QMatrix4x4(),m_textures_predefined.value(0),m_handler->NodeFromIndex(x).getColor(),QVector2D(1,1),m_program,pMatrix);
//       }

       // draw each node to the scene
//       for(int z = 0; z<m_handler->count();z++){
//         for(int l = 0;l<m_handler->NodeFromIndex(z).countConnected();l++)
//           DrawGL::DrawLine(m_handler->NodeFromIndex(z).Position(),m_handler->NodeFromIndex(m_handler->NodeFromIndex(z).getConnectedIndex(l)).Position(),
//                  vMatrix,QMatrix4x4(),QMatrix4x4(),QVector3D(0,0,0),m_program,pMatrix);
//       }
       for(int o = 0;o<m_handler->pathcount()-1;o++)
           DrawGL::DrawLine(m_handler->NodeFromIndex(m_handler->pathindex(o)).Position(),m_handler->NodeFromIndex(m_handler->pathindex(o+1)).Position(),
                vMatrix,QMatrix4x4(),QMatrix4x4(),QVector3D(0,1,0),m_program,pMatrix);

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

