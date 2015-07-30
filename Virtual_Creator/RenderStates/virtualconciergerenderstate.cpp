#include "virtualconciergerenderstate.h"
#include <QFileDialog>

VirtualConciergeRenderstate::VirtualConciergeRenderstate(QWidget *parent): QOpenGLWidget(parent), program(0), start(0), end(0){
    // enable antialiasing (set the format of the widget)
    format.setSamples(4);
    this->setFormat(format);

    // clear the textures
    this->textures.clear();
    this->textures_predefined.clear();
    this->position = new QVector3D(0,0,0);
    this->handler = new NodeHandler();

    if(PremisesExporter::fileExists("VirtualConcierge/nodes.pvc"))
        this->handler->ReadFilePVC("VirtualConcierge/nodes.pvc");

    //this->handler->CalculateShortest(0,1);
    //find_path(0,5);
}

void VirtualConciergeRenderstate::find_path(int start, int end){
    if((this->handler->count()>start)&&(this->handler->count()>end))
        this->handler->CalculateShortest(start,end);

    // update the frame of the virtual concierge
    paintGL();
    update();
}

void VirtualConciergeRenderstate::LoadTextures(QString path){
    // clear the premises when not empty
    if(this->textures.count()>0)
        this->textures.clear();

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
                this->textures.push_back(texture);
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
    if(this->objects.count()>0)
        this->objects.clear();

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
                    if(texture_index<this->textures.count()){
                        VisualObject *object = new VisualObject(this->plane,this->textures[texture_index],
                                                                QVector3D(matrix[0],matrix[1],matrix[2]),
                                                                QVector3D(matrix[3],matrix[4],matrix[5]),"FloorPlan");
                    object->setScaling(QVector3D(matrix[6],matrix[7],matrix[8]));
                    this->objects.push_back(object);
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
    this->node = new ModelMesh(":/Sphere");
    this->plane = new ModelMesh(":/Plane");
    this->door = new ModelMesh("://DoorWay01");
    this->wall = new ModelMesh("://Wall01");
    this->tree = new ModelMesh("://Tree01");

    // load objects and textures
    if(PremisesExporter::fileExists("VirtualConcierge/textures.tl"))
        LoadTextures("VirtualConcierge/textures.tl");
    if(PremisesExporter::fileExists("VirtualConcierge/environment.env"))
        LoadObjects("VirtualConcierge/environment.env");
    // load shaders
    this->program = new QOpenGLShaderProgram();
    this->program->addShaderFromSourceFile(QOpenGLShader::Vertex,":/Vertex");
    this->program->addShaderFromSourceFile(QOpenGLShader::Fragment,":/Fragment");
    this->program->link();

}

void VirtualConciergeRenderstate::initializeGL(){
    // this initializes all the opengl functions
    initializeOpenGLFunctions();
    // texture test
    QOpenGLTexture *texture = new QOpenGLTexture(QImage("://Texture0").mirrored());
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    this->textures_predefined.append(texture);
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
       if(!this->program){LoadContent();}
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
       foreach(VisualObject *object, this->objects){
           QMatrix4x4 translation;
           translation.translate(object->getTranslation());
           QMatrix4x4 rotation;
           rotation.rotate(object->getRotation().y(),0,1,0);
           rotation.scale(object->getScaling());
           if(object->getType().compare("FloorPlan")!=0)
           DrawGL::DrawModel(object->getModelMesh(), vMatrix, translation,rotation,object->getTexture(),QVector3D(),QVector2D(object->getScaling().z(),object->getScaling().x()),this->program,pMatrix);
           else
           DrawGL::DrawModel(object->getModelMesh(), vMatrix, translation,rotation,object->getTexture(),QVector3D(),QVector2D(1,1),this->program,pMatrix);
        }

//       // draw each node to the scene
//       for(int x = 0; x<this->handler->count();x++){
//         // this is for the model transformation
//         QMatrix4x4 mMatrix;
//         // transform the position locally
//         mMatrix.translate(this->handler->NodeFromIndex(x).Position());
//         // draw different types of nodes, (connected & unconnected nodes & best path)
//         DrawGL::DrawModel(this->node,vMatrix,mMatrix,QMatrix4x4(),this->textures_predefined.value(0),this->handler->NodeFromIndex(x).getColor(),QVector2D(1,1),this->program,pMatrix);
//       }

       // draw each node to the scene
//       for(int z = 0; z<this->handler->count();z++){
//         for(int l = 0;l<this->handler->NodeFromIndex(z).countConnected();l++)
//           DrawGL::DrawLine(this->handler->NodeFromIndex(z).Position(),this->handler->NodeFromIndex(this->handler->NodeFromIndex(z).getConnectedIndex(l)).Position(),
//                  vMatrix,QMatrix4x4(),QMatrix4x4(),QVector3D(0,0,0),this->program,pMatrix);
//       }
       for(int o = 0;o<this->handler->pathcount()-1;o++)
           DrawGL::DrawLine(this->handler->NodeFromIndex(this->handler->pathindex(o)).Position(),this->handler->NodeFromIndex(this->handler->pathindex(o+1)).Position(),
                vMatrix,QMatrix4x4(),QMatrix4x4(),QVector3D(0,1,0),this->program,pMatrix);

       //DrawModel(this->plane, vMatrix, QMatrix4x4(),QMatrix4x4(),QVector3D(0,0,0));
       // release the program for this frame
       this->program->release();
       // disable the cullmode for the frame
       glDisable(GL_CULL_FACE);
       // disable the depthtest for the frame
       glDisable(GL_DEPTH_TEST);
       // finish up the opengl frame
       glFinish();

}

VirtualConciergeRenderstate::~VirtualConciergeRenderstate(){
    delete this->program;
}

