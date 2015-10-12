/* Copyright 2015 Ruan Luies */

#include  <QFileDialog>
#include <QPainter>
#include <QtMath>
#include <math.h>
#include "./virtualconciergerenderstate.h"
#include "./Functions/mathematics.h"

VirtualConciergeRenderstate::VirtualConciergeRenderstate(QWidget *parent):
    QOpenGLWidget(parent),
    program(0),
    start(0),
    end(0),
    movement_index(-1),
    movement_position(QVector3D(0, 0, 0)),
    dt_counter(0.0f),
    movement_speed(1.0f),
    access_wheelchair(false),
    access_feet(false),
    access_bicycle(false),
    access_vehicle(false),
    disable_antialiasing(false){

    // enable antialiasing (set the format of the widget)
    format.setSamples(4);

    // clear the textures
    this->textures.clear();
    this->textures_predefined.clear();
    this->position = new QVector3D(0, 0, 0);
    this->handler = new NodeHandler();

    if ( PremisesExporter::fileExists("VirtualConcierge/nodes.pvc") ) {
        this->handler->ReadFilePVC("VirtualConcierge/nodes.pvc");
        if ( this->handler->count() > 0 )
          movement_position = this->handler->NodeFromIndex(0).Position();
    }
    frame_update = new QTimer(this);

    connect(frame_update, SIGNAL(timeout()),
            this, SLOT(update_frame()));
    frame_update->start(5);
}

void VirtualConciergeRenderstate::antialiasing(bool value) {
    this->disable_antialiasing = value;
    if ( !this->disable_antialiasing ) {
        this->setFormat(format);
    }
}

void VirtualConciergeRenderstate::change_speed(float speed) {
  movement_speed = speed;
}

void VirtualConciergeRenderstate::pause(bool value) {
  if ( value ) {
      frame_update->stop();
  } else {
      frame_update->start(5);
  }
}

void VirtualConciergeRenderstate::reset_everything() {
this->handler->CalculateShortest(0, 0, true, true, true, true);
}

void VirtualConciergeRenderstate::update_frame() {

    if ( (this->handler->pathcount() > 0) && (this->handler->pathcount() > movement_index) && (movement_index > - 1) ) {
      QVector3D temp = this->handler->NodeFromIndex(this->handler->pathindex(movement_index)).Position() - movement_position;
      temp.normalize();

      movement_position += movement_speed * temp * 0.025f;
      if (movement_position.distanceToPoint(this->handler->NodeFromIndex(this->handler->pathindex(movement_index)).Position()) < 0.5f)
      movement_index--;
    }
    // update the frame of the virtual concierge
    this->update();
    dt_counter += 0.01f;
}

void VirtualConciergeRenderstate::find_path(int start, int end) {
  if ( (this->handler->count() > start) &&
       (this->handler->count() > end) ) {
      movement_index = this->handler->pathcount() - 1;
      //movement_position = this->handler->NodeFromIndex(0).Position();
      this->handler->CalculateShortest(start, end, this->access_feet,
                                       this->access_wheelchair,
                                       this->access_vehicle,
                                       this->access_bicycle);
  }

  // update the frame of the virtual concierge
  this->update();

  if ( (this->handler->count() > start) &&
       (this->handler->count() > end) ) {
      movement_index = this->handler->pathcount() - 1;
      movement_position = this->handler->NodeFromIndex(0).Position();
      this->handler->CalculateShortest(start, end, this->access_feet,
                                       this->access_wheelchair,
                                       this->access_vehicle,
                                       this->access_bicycle);
  }

  // update the frame of the virtual concierge
  this->update();
}

void VirtualConciergeRenderstate::LoadTextures(QString path) {
  // clear the premises when not empty
  if ( this->textures.count() > 0 )
    this->textures.clear();

  /* populate the textures from the text file */

  // load the text file
  QFile textfile(path);

  // open the text file
  textfile.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream ascread(&textfile);

  if ( textfile.isOpen() ) {
    // read each line of the file
    QString line = ascread.readLine();
    while ( !line.isNull() ) {
      // break the line up in usable parts
      QStringList list = line.split(",");
      // check the type of line
      if ( list[0] == "t" ) {
        int texture_index = 0;
        QString texture_path ="";

        // texture type
        QTextStream(&list[2]) >> texture_path;

        // texture index
        QTextStream(&list[1]) >> texture_index;

        // load texture
        QOpenGLTexture *texture =
                new QOpenGLTexture(QImage(texture_path).mirrored());
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

void VirtualConciergeRenderstate::LoadObjects(QString path) {
  // clear the premises when not empty
  if ( this->objects.count() > 0 )
    this->objects.clear();

  /* populate the premisis from the text file */

  // load the text file
  QFile textfile(path);

  // open the text file
  textfile.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream ascread(&textfile);

  if ( textfile.isOpen() ) {
    // read each line of the file
    QString line = ascread.readLine();
    while ( !line.isNull() ) {
      // break the line up in usable parts
      QStringList list = line.split(",");
      // check the type of line
        if ( list[0] == "o" ) {
          // this is only x,y,z coordinates for the node
          float matrix[9];
          int texture_index = 0;
          QString Type = "";
          // populate the vertices
          for ( int i = 0; i < 9; i++)
            QTextStream(&list[i + 3]) >> matrix[i];
          // texture index
          QTextStream(&list[12]) >> texture_index;

          // object type
          QTextStream(&list[2]) >> Type;

          // add floorplan
          if ( Type.compare("FloorPlan", Qt::CaseInsensitive) == 0 ) {
            if ( texture_index < this->textures.count() ) {
              VisualObject *object
                      = new VisualObject(this->plane,
                                         this->textures[texture_index],
                                         QVector3D(matrix[0],
                                                   matrix[1],
                                                   matrix[2]),
                                         QVector3D(matrix[3],
                                                   matrix[4],
                                                   matrix[5]),
                                                   "FloorPlan");
              object->setScaling(QVector3D(matrix[6],
                                           matrix[7],
                                           matrix[8]));
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

void VirtualConciergeRenderstate::LoadContent() {
  // this initializes all the opengl functions
  initializeOpenGLFunctions();

  // load meshes
  this->node = new ModelMesh(":/Sphere");
  this->plane = new ModelMesh(":/Plane");
  this->door = new ModelMesh("://DoorWay01");
  this->wall = new ModelMesh("://Wall01");
  this->tree = new ModelMesh("://Tree01");
  this->arrow = new ModelMesh(":/Content/arrow.obj");
  this->youarehere = new ModelMesh(":/Content/youarehere.obj");
  this->destination = new ModelMesh(":/Content/destination.obj");
  // load environment and textures
  if ( PremisesExporter::fileExists("VirtualConcierge/textures.tl"))
     LoadTextures("VirtualConcierge/textures.tl");
  if ( PremisesExporter::fileExists("VirtualConcierge/environment.env"))
    LoadObjects("VirtualConcierge/environment.env");

  // load shaders, both the vertex and pixel shader
  this->program = new QOpenGLShaderProgram();
  this->program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         ":/Vertex");
  this->program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         ":/Fragment");
  this->program->link();

  // load texture
  texture_you_are_here =
          new QOpenGLTexture(QImage(":/Content/arrow.bmp").mirrored());
  texture_you_are_here->setMinificationFilter(QOpenGLTexture::Linear);
  texture_you_are_here->setMagnificationFilter(QOpenGLTexture::Linear);
}

void VirtualConciergeRenderstate::initializeGL() {
    // this initializes all the opengl functions
    initializeOpenGLFunctions();
    // texture test
    QOpenGLTexture *texture =
            new QOpenGLTexture(QImage("://Texture0").mirrored());
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    this->textures_predefined.append(texture);
    // glReadBuffer(GL_FRONT);
}

void VirtualConciergeRenderstate::resizeGL(int w, int h) {
    // setup the viewport for opengl
    glViewport(0, 0, w, h);

    // initialize the projection matrix
    pMatrix.setToIdentity();

    // set the projection matrix
    pMatrix.perspective(45,
                        static_cast<float>(w) / static_cast<float>(h),
                        1.0f, 1000.0f);
}

void VirtualConciergeRenderstate::receive_access(bool wheelchair, bool feet, bool bicycle, bool vehicle) {
  this->access_wheelchair = wheelchair;
  this->access_feet = feet;
  this->access_bicycle = bicycle;
  this->access_vehicle = vehicle;
}

void VirtualConciergeRenderstate::paintGL() {
  //if ( this->handler->count() > 0 )
   //   middel = this->handler->NodeFromIndex(0).Position();


  // define a view matrix
  QMatrix4x4 vMatrix;
  // whenever content is not loaded, load the content
  if ( !this->program ) { LoadContent();}
  // enable the scene's depth mask
  glDepthMask(GL_TRUE);
  // clear the depth z = 0.0f -> 1.0f
  glClearDepth(1.0f);
  // enable the scene's depth test
  glEnable(GL_DEPTH_TEST);
  // enable cullmode CCW (counter clockwise)
  glEnable(GL_CULL_FACE);
  // enable transparency
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // clear the background color for rendering
  // cornflower blue 659CEF
  glClearColor(210.0/255.0, 210.0/255.0, 210.0/255.0, 1);
  // clear the color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  // setup camera
  QMatrix4x4 cameraTransformation;
  // rotation in the y - axis
  cameraTransformation.rotate(0, 0, 1, 0);
  // rotation in the x - axis
  cameraTransformation.rotate(-90, 1, 0, 0);
  // transform the camera's position with respect to the rotation matrix
  QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, 40.0);
  // define the direction of the camera's up vector
  QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);
  // implement and transform the camera
  vMatrix.lookAt(cameraPosition  + movement_position, movement_position, cameraUpDirection);
  double sum_rotate = 0;
  // draw node lines and arrows
  for ( int o = 0; o < this->handler->pathcount() - 1; o++ ) {
    QVector3D first_position = this->handler->
              NodeFromIndex(this->handler->pathindex(o)).Position();
    QVector3D second_position = this->handler->
              NodeFromIndex(this->handler->pathindex(o+1)).Position();
  DrawGL::DrawLine(first_position + QVector3D(0, 0.1, 0),
                   second_position + QVector3D(0, 0.1, 0),
                   vMatrix, QMatrix4x4(), QMatrix4x4(),
                   QVector3D(0, 0.98, 0), this->program, pMatrix,
                   0.0f);

  QMatrix4x4 translation;
  translation.translate((first_position + second_position)/2.0);
  QMatrix4x4 rotation;
  double distance = first_position.distanceToPoint(second_position);

  sum_rotate = (180.0 / M_PI) * asin((first_position.z() - second_position.z())/distance) + 180 ;
  if ( first_position.x() - second_position.x() > 0) {
    sum_rotate = -(180.0 / M_PI) * asin((first_position.z() - second_position.z())/distance);
  }
  rotation.rotate(sum_rotate, 0, 1, 0);
  rotation.scale(0.5);
  if ( movement_index < o)
  DrawGL::DrawModel(this->arrow,
                    vMatrix,
                    translation,
                    rotation,
                    texture_you_are_here,
                    QVector3D(0, 1, 0),
                    QVector2D(1, 1),
                    this->program, pMatrix, movement_position.y());
  else
      DrawGL::DrawModel(this->arrow,
                        vMatrix,
                        translation,
                        rotation,
                        texture_you_are_here,
                        QVector3D(),
                        QVector2D(1, 1),
                        this->program, pMatrix, movement_position.y());
  }
  QMatrix4x4 translation;
  if ( this->handler->count() > 0 )
  translation.translate(this->handler->NodeFromIndex(0).Position() + QVector3D(0, 0.2, 0));
  QMatrix4x4 rotation;
  rotation.rotate(0, 0, 1, 0);
  rotation.scale(0.75, 0.1, 0.75);
  DrawGL::DrawModel(this->youarehere,
                    vMatrix,
                    translation,
                    rotation,
                    texture_you_are_here,
                    QVector3D(),
                    QVector2D(1, 1),
                    this->program, pMatrix, movement_position.y());
  QMatrix4x4 translation_destination;
  if ( this->handler->pathcount() > 0 ) {
  translation_destination.translate(this->handler->NodeFromIndex(this->handler->pathindex(0)).Position() + QVector3D(0, 0.2, 0));
  QMatrix4x4 rotation_destination;
  rotation_destination.rotate(0, 0, 1, 0);
  rotation_destination.scale(0.75 * ( 1 + sin(dt_counter) * 0.2), 0.1, 0.75 * (1 + sin(dt_counter) * 0.2));
  DrawGL::DrawModel(this->destination,
                    vMatrix,
                    translation_destination,
                    rotation_destination,
                    texture_you_are_here,
                    QVector3D(0, 0, 0),
                    QVector2D(1, 1),
                    this->program, pMatrix, movement_position.y());
  }
  // draw other objects first

    foreach(VisualObject *object, this->objects) {
    QMatrix4x4 translation;
    translation.translate(object->getTranslation());
    QMatrix4x4 rotation;
    rotation.rotate(object->getRotation().y(), 0, 1, 0);
    rotation.scale(object->getScaling());
    if ( object->getType().compare("FloorPlan") != 0 )
      DrawGL::DrawModel(object->getModelMesh(),
                        vMatrix,
                        translation,
                        rotation,
                        object->getTexture(),
                        QVector3D(),
                        QVector2D(object->getScaling().z(),
                                  object->getScaling().x()),
                        this->program, pMatrix, movement_position.y());
    else
      DrawGL::DrawModel(object->getModelMesh(),
                        vMatrix, translation,
                        rotation, object->getTexture(),
                        QVector3D(), QVector2D(1, 1),
                        this->program, pMatrix, movement_position.y());
  }

  // release the program for this frame
  this->program->release();
  // disable the cullmode for the frame
  glDisable(GL_CULL_FACE);
  // disable the depthtest for the frame
  glDisable(GL_DEPTH_TEST);
  // finish up the opengl frame
  glFinish();
  // draw the nodes to the scene
  QPainter painter;
  painter.begin(this);
  painter.setPen(Qt::white);
  QFont serifFont("Arial", 10, QFont::Bold);
  painter.setFont(serifFont);
  if ( !this->disable_antialiasing ) {
    painter.setRenderHints(QPainter::Antialiasing |
                          QPainter::SmoothPixmapTransform);
  }
  // draw all the node text here
  for ( int l = 0; l < this->handler->count(); l++) {
    QPoint pos_x_y =
      Mathematics::transform_3d_to_2d(vMatrix,
                                      this->pMatrix,
                                      this->handler->NodeFromIndex(l).Position(),
                                      this->width(),
                                      this->height());
    if ( this->handler->NodeFromIndex(l).getSignificant() &&
         ( this->handler->NodeFromIndex(l).Position().y() < this->movement_position.y() + 0.5 ) &&
         ( this->handler->NodeFromIndex(l).Position().y() > this->movement_position.y() - 0.5 ) ) {
     // painter.drawText(pos_x_y.x() - (this->handler->NodeFromIndex(l).getName().length() * 4), pos_x_y.y() + 5, this->handler->NodeFromIndex(l).getName());
    }
  }

  painter.end();
}

VirtualConciergeRenderstate::~VirtualConciergeRenderstate() {
  delete this->program;
}

