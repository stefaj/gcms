/* Copyright 2015 Ruan Luies */

#include <algorithm>
#include "./renderstate.h"
#include "Functions/mathematics.h"

RenderState::RenderState(QWidget *parent): QOpenGLWidget(parent),
    program(0),
    mouse_x(0),
    mouse_y(0),
    node_index_selected(-1),
    mouse_zoom(60.0f),
    noderadius(0.5f),
    mouse_y_inverted(1.0f),
    current_floor_height(0.0f),
    position_camera(QVector3D()),
    camera_prev(QVector3D()),
    raycast(QVector3D()),
    rotation(QVector3D()),
    currentscale(QVector3D(1, 1, 1)),
    drag_middle_position(QVector3D()),
    corner_1(QVector3D()),
    corner_2(QVector3D()),
    corner_3(QVector3D()),
    corner_4(QVector3D()),
    center_h_1(QVector3D()),
    center_h_2(QVector3D()),
    mousedown_right(false),
    mousedown_left(false),
    node_placable(false),
    pavement_placable(false),
    tree_placable(false),
    placable_floor_plan(false),
    node_significant(true),
    tree_radius(4.0f),
    infinte_lenght_lines(100.0f),
    selected_label(this) {
    // enable antialiasing (set the format of the widget)
    QSurfaceFormat format;
    format.setSamples(4);
    this->setFormat(format);

    // initialize the clicked position
    this->clicked_position = new QVector3D();

    // set the current mouse position in 3D
    this->current_position = new QVector3D();

    // clear the textures
    this->textures.clear();

    // set the position to initial null vector
    this->position = new QVector3D();

    // clear the nodes
    this->nodes.clear();

    // clear visual objects
    this->models.clear();

    // set mouse tracking
    setMouseTracking(true);
}

void RenderState::allow_node(bool value) {this->node_placable = value;}

void RenderState::invert_mouseY(bool value) {
    if (value)
        this->mouse_y_inverted = -1.0f;
    else
        this->mouse_y_inverted = 1.0f;
}

void RenderState::load_premises(QString value) {
  // get the path of each subdirectory
  QStringList ls = value.split("/");

  // count the subdirectories
  int append = ls.count();
  QString directory_path = "";

  // create new file path from previous
  for ( int k = 0; k < append-1; k++ ) {
    directory_path += ls[k]+"/";
  }
  // load textures and objects
  LoadTextures(directory_path);
  LoadObjects(value);
  LoadNodes(directory_path);
  // export the files afterwards
  PremisesExporter::export_environment(this->models,
                                       "environment.env");
  PremisesExporter::export_texture(this->texture_paths,
                                   "textures.tl");
  PremisesExporter::export_nodes(this->nodes,
                                 "nodes.pvc");
}

void RenderState::set_next_node_name(QString value) {
    this->next_node_name = value;
}

void RenderState::set_next_node_significant(bool value) {
    this->node_significant = value;
}

void RenderState::allow_remove_node(bool value) {
    this->node_removable = value;
}

void RenderState::allow_remove_tree(bool value) {
    this->tree_removable = value;
}

void RenderState::allow_link(bool value) {
    this->node_linkable = value;
}

void RenderState::allow_pavement(bool value) {
    this->pavement_placable = value;
}

void RenderState::allow_door(bool value) {
    this->door_placeable = value;
}

void RenderState::allow_wall(bool value) {
    this->wall_placable = value;
}

void RenderState::allow_tree(bool value) {
    this->tree_placable = value;
}

void RenderState::allow_floor_plan(bool value) {
    this->placable_floor_plan = value;
}

void RenderState::change_rotY(double value) {
    this->rotation.setY(value);
}

void RenderState::set_object_scale(QVector3D value) {
    this->currentscale = value;
}

void RenderState::change_current_floor_height(float value) {
    this->current_floor_height = value;
}

void RenderState::load_texture_from_file(QString value) {
  QString val_new = "VirtualConcierge/" +
          QString("TEX") +
          QString::number(this->texture_paths.count());

  // try to copy the texture to the drive
  if ( !QFile::copy(value, val_new) ) {
    if ( !QFile::exists(val_new) ) {
      QMessageBox::warning(this,
                           tr("Error file copying"),
                           tr("Texture file could not"
                              " be copied to the drive."));
    }
  }

  // add texture to the lists
  QOpenGLTexture* texture = new QOpenGLTexture(QImage(value).mirrored());
  texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  this->textures_from_files.push_back(texture);
  this->texture_paths.push_back(val_new);
}

void RenderState::initializeGL() {
  initializeOpenGLFunctions();
  // texture test
  for ( int i = 0; i < 5; i++ ) {
  QOpenGLTexture *texture =
          new QOpenGLTexture(QImage("://Texture" +
                                    QString::number(i)).mirrored());
  texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  this->textures.push_back(texture);
  }
}

void RenderState::mouseMoveEvent(QMouseEvent *event) {
    // alert mouse event's position (x)
    this->mouse_x = event->x();

    // alert mouse event's position (x)
    this->mouse_y = event->y();

    // update raycast vector
    this->raycast = Mathematics::mouse_raycast(this->mouse_x,
                                               this->mouse_y,
                                               this->width(),
                                               this->height(),
                                               this->mouse_y_inverted,
                                               vMatrix, pMatrix);

    if ( this->mousedown_right ) {
        this->position_camera.setX(this->clicked_position->x() -
                                   this->current_position->x());
        this->position_camera.setY(this->clicked_position->y() -
                                   this->current_position->y());
        this->position_camera.setZ(this->clicked_position->z() -
                                   this->current_position->z());

        // pan view
        this->camera_prev.setX(this->camera_prev.x() -
                               this->position_camera.x());
        this->camera_prev.setY(this->camera_prev.y() -
                               this->position_camera.y());
        this->camera_prev.setZ(this->camera_prev.z() -
                               this->position_camera.z());
        this->position_camera = QVector3D(0, 0, 0);
    }

  // removable dragable nodes
  if ( this->mousedown_left && this->node_removable ) {
    RemoveNodes();
  }

  // update openGL widget
  update();
}

void RenderState::mouseReleaseEvent(QMouseEvent * /*event*/) {
    // release button right click
    if ( this->mousedown_right )
    this->mousedown_right = false;

    // button left click released
    if ( this->mousedown_left ) {
        this->mousedown_left = false;

        if ( this->node_linkable ) {
            int linkindex = -1;
            // get position of the clicked
            this->clicked_position = new QVector3D(this->current_position->x(),
                                                   this->current_position->y(),
                                                   this->current_position->z());

            // collision detection
            for ( int l = 0; l < this->nodes.count(); l++ ) {
                if ( this->clicked_position->
                     distanceToPoint(this->nodes.value(l)->Position()) <
                     this->noderadius )
                    linkindex = l;
            }
            if ( (linkindex > -1) &&
                 (this->node_index_selected > -1) &&
                 (this->node_index_selected < this->nodes.count()) ) {
                const unsigned int countConnected =
                        this->
                        nodes.value(this->node_index_selected)->
                        countConnected();
                // add a link to the node
                this->nodes.value(this->node_index_selected)->
                        AddLink(new QString("Link" +
                                            QString::number(countConnected)),
                                linkindex);
            }
            // export to temp nodes
            PremisesExporter::export_nodes(this->nodes,
                                           "nodes.pvc");
        }

        if ( this->wall_placable ) {
            // place wall
             add_wall(this->rotation,
                      this->drag_middle_position,
                      QVector3D(1, 1, this->currentscale.z()));
        }

        if ( this->pavement_placable ) {
            // place pavement
            add_pavement(this->rotation,
                         *this->clicked_position,
                         this->currentscale);
        }
    }

    this->clicked_position = new QVector3D(0, -1000, 0);
    this->rotation = QVector3D();
    // this->currentscale = QVector3D(1, 1, 1);
    // update the frame
    update();
}

void RenderState::mousePressEvent(QMouseEvent *event) {
    // make dragable from left click
    if ( event->button() == Qt::LeftButton)
    this->mousedown_left = true;

    // right click to move the camara around
    if ( event->button() == Qt::RightButton)
        this->mousedown_right = true;

    // left click to add the node
    if ( (event->button() == Qt::LeftButton) && (this->node_placable) ) {
        add_node(new QString(this->next_node_name));
        PremisesExporter::export_nodes(this->nodes, "nodes.pvc");
    }

    // left click to add door
    if ( (event->button() == Qt::LeftButton) && (this->door_placeable) )
        add_door(this->rotation, *this->current_position, this->currentscale);

    // add floor plan
    if ( (event->button() == Qt::LeftButton) && (this->placable_floor_plan) )
        add_floor_plan(this->rotation,
                       *this->current_position,
                       this->currentscale);

    // left click to add wall
    if ( (event->button() == Qt::LeftButton) && (this->wall_placable) )
        this->clicked_position = new QVector3D(this->current_position->x(),
                                               this->current_position->y(),
                                               this->current_position->z());

    // left click to add tree
    if ( (event->button() == Qt::LeftButton) && (this->tree_placable) )
        add_tree(this->rotation, *this->current_position, this->currentscale);

    // set current clicked position
    this->clicked_position = new QVector3D(this->current_position->x(),
                                           this->current_position->y(),
                                           this->current_position->z());

    if ( (event->button() == Qt::LeftButton) && (this->tree_removable) ) {
        for ( int k = 0 ; k < this->models.count(); k++ ) {
            if ( (this->models.value(k)->
                  getType().compare("Tree",
                                    Qt::CaseInsensitive) == 0) &&
                 (this->models.value(k)->
                  getTranslation().distanceToPoint(*this->current_position) <
                  tree_radius) ) {
                this->models.removeAt(k);
            }
        }
    }

  // left click to remove the node
  if ( (event->button() == Qt::LeftButton) && (this->node_removable) ) {
    RemoveNodes();
  }

  // left click to add the link
  if ( (event->button() == Qt::LeftButton) && (this->node_linkable) ) {
    // get position of the clicked
    this->clicked_position = new QVector3D(this->current_position->x(),
                                           this->current_position->y(),
                                           this->current_position->z());

    // collision detection
    for ( int l = 0; l < this->nodes.count(); l++ ) {
      if ( this->clicked_position->
           distanceToPoint(this->nodes.value(l)->Position()) < this->noderadius)
        this->node_index_selected = l;
    }
  }
}

void RenderState::RemoveNodes() {
  // collision detection
  for ( int l = 0; l < this->nodes.count(); l++ ) {
    if ( this->current_position->distanceToPoint(this->
                                               nodes.value(l)->
                                               Position()) <
      this->noderadius ) {
      // remove node
      this->nodes.removeAt(l);

      // remove all dependencies
      for ( int i = 0; i < this->nodes.count(); i++ ) {
        const unsigned int count_connected =
                this->nodes.value(i)->countConnected();
        // remove all the links of the deleted node
        for ( unsigned int z = 0; z < count_connected; z++ ) {
          if ( this->nodes.value(i)->getConnectedIndex(z) == l)
            this->nodes.value(i)->RemoveLinkedFromIndex(z);
        }

        // move the links back after the node was deleted
        for ( unsigned int k = 0; k < count_connected; k++ ) {
          if ( this->nodes.value(i)->getConnectedIndex(k) > l )
            this->nodes.value(i)->MoveLinkedIndexBack(k);
        }
      }
    }
  }
  // update the temp nodelist
  PremisesExporter::export_nodes(this->nodes, "nodes.pvc");
}

void RenderState::wheelEvent(QWheelEvent *event) {
    // camera zoom with the mouse scroll
    this->mouse_zoom -= static_cast<float>(event->delta()) / 120.0f;

    // limit the zoom
    if ( this->mouse_zoom < 2.0f)
        this->mouse_zoom = 2.0f;

    // update the openGL frame after the zoom
    update();
}

void RenderState::add_node(QString *name) {
    // create new nodes
    Node *newnode = new Node(new QVector3D(this->current_position->x(),
                                           this->current_position->y(),
                                           this->current_position->z()),
                                           name);
    // set significance
    newnode->setSignificant(this->node_significant);

    // add new node to vector
    this->nodes.push_back(newnode);
}

void RenderState::add_pavement(QVector3D rotation,
                               QVector3D translation,
                               QVector3D scaling) {
    // texture index 1 is the tile
    VisualObject * object = new VisualObject(this->plane,
                                             this->textures.value(1),
                                             translation,
                                             rotation,
                                             "Pavement");
    object->setScaling(scaling);
    this->models.push_back(object);
    PremisesExporter::export_environment(this->models, "environment.env");
    PremisesExporter::export_texture(this->texture_paths, "textures.tl");
    object->setTextureID(701);
    object->setTexturePath("://Texture1");
}

void RenderState::add_tree(QVector3D rotation,
                           QVector3D translation,
                           QVector3D scaling) {
    // texture index 1 is the tile
    VisualObject * object = new VisualObject(this->tree,
                                             this->textures.value(2),
                                             translation,
                                             rotation,
                                             "Tree");
    object->setScaling(scaling);
    this->models.push_back(object);
    PremisesExporter::export_environment(this->models, "environment.env");
    PremisesExporter::export_texture(this->texture_paths, "textures.tl");
    object->setTextureID(702);
    object->setTexturePath("://Texture2");
}

void RenderState::add_wall(QVector3D rotation,
                           QVector3D translation,
                           QVector3D scaling) {
    // texture index 1 is the tile
    VisualObject * object = new VisualObject(this->wall,
                                             this->textures.value(4),
                                             translation, rotation,
                                             "Wall");
    object->setScaling(scaling);
    // set horizontal centers
    object->setLMidHorisontal(this->center_h_1);
    object->setUMidHorisontal(this->center_h_2);
    this->models.push_back(object);
    object->setTextureID(704);
    object->setTexturePath("://Texture4");
    PremisesExporter::export_environment(this->models, "environment.env");
    PremisesExporter::export_texture(this->texture_paths, "textures.tl");
}

void RenderState::add_door(QVector3D rotation,
                           QVector3D translation,
                           QVector3D scaling) {
    // texture index 1 is the tile
    VisualObject * object = new VisualObject(this->door,
                                             this->textures.value(2),
                                             translation,
                                             rotation,
                                             "Door");
    object->setScaling(scaling);
    object->setTextureID(702);
    object->setTexturePath("://Texture2");
    this->models.push_back(object);
    PremisesExporter::export_environment(this->models, "environment.env");
    PremisesExporter::export_texture(this->texture_paths, "textures.tl");
}

void RenderState::add_floor_plan(QVector3D rotation,
                                 QVector3D translation,
                                 QVector3D scaling) {
    // texture index 1 is the tile
    VisualObject * object =
            new VisualObject(this->plane,
                             this->
                             textures_from_files.
                             value(this->
                                   textures_from_files.count() -
                                   1),
                             translation,
                             rotation,
                             "FloorPlan");
    object->setScaling(scaling);
    object->setTextureID(this->textures_from_files.count() - 1);
    object->setTexturePath(this->
                           texture_paths.value(this->
                                               textures_from_files.count() -
                                               1));
    this->models.push_back(object);
    PremisesExporter::export_environment(this->models, "environment.env");
    PremisesExporter::export_texture(this->texture_paths, "textures.tl");
}

void RenderState::resizeGL(int w, int h) {
    // setup the viewport for opengl
    glViewport(0, 0, w, h);

    // initialize the projection matrix
    pMatrix.setToIdentity();

    // set the projection matrix
    pMatrix.perspective(45,
                        static_cast<float>(w) /
                        static_cast<float>(h),
                        1.0f,
                        1000.0f);
}

void RenderState::LoadContent() {
    // this initializes all the opengl functions
    initializeOpenGLFunctions();

    // load meshes
    this->node = new ModelMesh(":/Sphere");
    this->plane = new ModelMesh(":/Plane");
    this->door = new ModelMesh("://DoorWay01");
    this->wall = new ModelMesh("://Wall01");
    this->tree = new ModelMesh("://Tree01");

    // load shaders
    this->program = new QOpenGLShaderProgram();

    // load vertex shader (the geometry of the 3D objects )
    this->program->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           "://Vertex");

    // load the pixel/fragment shader.
    // this is the pixel shader (per pixel rendering)
    this->program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           "://Fragment");

    // link the shaders
    this->program->link();
}

void RenderState::paintGL() {
  // initialise the view matrix
  vMatrix.setToIdentity();
  // whenever content is not loaded, load the content
  if ( !this->program ) {
      LoadContent();
      // checkout opengl context
      emit opengl_initialised(this->context()->isValid());
  }
  // enable the scene's depth mask
  glDepthMask(GL_TRUE);
  // clear the depth z = 0.0f -> 1.0f
  glClearDepth(1.0f);
  // enable the scene's depth test
  glEnable(GL_DEPTH_TEST);
  // enable cullmode CCW (counter clockwise)
  glEnable(GL_CULL_FACE);
  // clear the background color for rendering
  glClearColor(104.0/255.0, 104.0/255.0, 104.0/255.0, 1);
  // clear the color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // setup camera
  QMatrix4x4 cameraTransformation;
  // rotation in the y - axis
  cameraTransformation.rotate(0, 0, 1, 0);
  // rotation in the x - axis
  cameraTransformation.rotate(-90, 1, 0, 0);
  // transform the camera's position with respect to the rotation matrix
  QVector3D cameraPosition = cameraTransformation *
          QVector3D(0,
                    0,
                    this->mouse_zoom +
                    this->current_floor_height);
  // define the direction of the camera's up vector
  QVector3D cameraUpDirection = cameraTransformation *
          QVector3D(0, 1, 0);
  // implement and transform the camera
 vMatrix.lookAt(cameraPosition,
                QVector3D(0,
                          this->current_floor_height,
                          0),
                cameraUpDirection);
  vMatrix.translate(this->camera_prev);

  // return the position of the ray intersection with the y-axis
  QVector3D Pos  = Mathematics::intersectYat(this->raycast,
                                             QVector3D(0,
                                                       this->mouse_zoom,
                                                       0) -
                                             this->camera_prev,
                                             this->current_floor_height);

  // update current position
  this->current_position->setX(Pos.x());
  this->current_position->setZ(Pos.z());
  this->current_position->setY(Pos.y());

  // draw other objects first
  foreach(VisualObject *object, this->models) {
    QMatrix4x4 translation;
    translation.translate(object->getTranslation());
    QMatrix4x4 rotation;
    rotation.rotate(object->getRotation().y(), 0, 1, 0);
    rotation.scale(object->getScaling());
    if ( object->getType().compare("FloorPlan") != 0 )
      DrawGL::DrawModel(object->getModelMesh(),
                        vMatrix, translation,
                        rotation, object->getTexture(),
                        QVector3D(),
                        QVector2D(object->getScaling().z(),
                                  object->getScaling().x()),
                        this->program,
                        pMatrix);
    else
        DrawGL::DrawModel(object->getModelMesh(),
                          vMatrix, translation,
                          rotation, object->getTexture(),
                          QVector3D(), QVector2D(1, 1),
                          this->program, pMatrix);
      if ( this->wall_placable ) {
        if ( object->getLMidHorisontal().distanceToPoint(Pos) < 0.25f )
          *this->current_position = object->getLMidHorisontal();
        if ( object->getUMidHorisontal().distanceToPoint(Pos) < 0.25f )
          *this->current_position = object->getUMidHorisontal();
      }
  }

  // draw placable node
  DrawGL::draw_if_true(this->node, vMatrix,
                       Pos, this->rotation,
                       QVector3D(1, 1, 1),
                       this->textures.value(0),
                       QVector3D(1, 0, 0),
                       QVector2D(1, 1),
                       pMatrix, this->program,
                       this->node_placable
                       && this->node_significant);

  // draw placable node (not significant)
  DrawGL::draw_if_true(this->node, vMatrix,
                       Pos, this->rotation,
                       QVector3D(1, 1, 1),
                       this->textures.value(0),
                       QVector3D(), QVector2D(1, 1),
                       pMatrix, this->program,
                       this->node_placable
                       && !this->node_significant);

  // draw placable tile draggable mouse
  DrawGL::draw_if_true(this->plane, vMatrix,
                       Pos, this->rotation,
                       QVector3D(1, 1, 1),
                       this->textures.value(1),
                       QVector3D(),
                       QVector2D(this->currentscale.z(),
                                 this->currentscale.x()),
                       pMatrix, this->program,
                       this->pavement_placable
                       && (!this->mousedown_left));
  // draw placable tile clicked
  if ( this->mousedown_left && this->pavement_placable ) {
    this->currentscale.setZ(pow(pow((this->clicked_position->z() -
                                     this->current_position->z()), 2),
                                0.5) * 2.0);
    this->currentscale.setY(1);
    this->currentscale.setX(pow(pow((this->clicked_position->x() -
                                     this->current_position->x()), 2),
                                0.5) * 2.0);
  }
  // draw pavement
  DrawGL::draw_if_true(this->plane, vMatrix,
                       *this->clicked_position,
                       this->rotation, this->currentscale,
                       this->textures.value(1), QVector3D(),
                       QVector2D(this->currentscale.z(),
                                 this->currentscale.x()),
                       pMatrix, this->program,
                       this->pavement_placable
                       && (this->mousedown_left));

  // draw placable door
  DrawGL::draw_if_true(this->door, vMatrix,
                       Pos, this->rotation,
                       QVector3D(1, 1, 1),
                       this->textures.value(2),
                       QVector3D(), QVector2D(1, 1),
                       pMatrix, this->program,
                       this->door_placeable);

  // draw placable wall
  if ( (this->mousedown_left) && (this->wall_placable) ) {
    this->drag_middle_position = (*this->clicked_position +
                                  *this->current_position) / 2.0;
    this->rotation.setY(Mathematics::flat_angle_from_vectors(
                            *this->clicked_position,
                            *this->current_position) + 90);

    // clamp to 0 and 180 degrees
    if ( (Mathematics::return_near_degree(this->rotation.y()) == 0.0)
         || (Mathematics::return_near_degree(this->rotation.y()) == 180) ) {
      // set fixed rotation for the rotation
      this->rotation.setY(Mathematics::return_near_degree(this->rotation.y()));

      // set fixed position for the  x - axis
      this->drag_middle_position.setX(this->clicked_position->x());
      this->current_position->setX(this->clicked_position->x());

      DrawGL::DrawLine(*this->clicked_position +
                       QVector3D(0, 0, -infinte_lenght_lines),
                       *this->current_position +
                       QVector3D(0, 0, infinte_lenght_lines),
                       vMatrix, QMatrix4x4(), QMatrix4x4(),
                       QVector3D(1, 1, 1), this->program, pMatrix);
    }

      // clamp to 270 and 90 degrees
      if ( (Mathematics::return_near_degree(this->rotation.y()) == 270)
           || (Mathematics::return_near_degree(this->rotation.y()) == 90)
           || (Mathematics::return_near_degree(this->rotation.y()) == -90) ) {
        this->rotation.setY(Mathematics::return_near_degree(this->
                                                              rotation.y()));
        this->drag_middle_position.setZ(this->clicked_position->z());
        this->current_position->setZ(this->clicked_position->z());
        DrawGL::DrawLine(*this->clicked_position +
                         QVector3D(-infinte_lenght_lines, 0, 0),
                         *this->current_position +
                         QVector3D(infinte_lenght_lines, 0, 0),
                         vMatrix, QMatrix4x4(), QMatrix4x4(),
                         QVector3D(1, 1, 1), this->program, pMatrix);
      }
      // set clickable centers
      this->center_h_1 = *this->current_position;
      this->center_h_2 = *this->clicked_position;

      this->currentscale.setZ(this->clicked_position->
                                distanceToPoint(*this->current_position));
      DrawGL::draw_if_true(this->wall,  vMatrix, this->drag_middle_position,
                           this->rotation,
                           QVector3D(1, 1, this->currentscale.z()),
                           this->textures.value(4), QVector3D(),
                           QVector2D(this->currentscale.z(), 1.0),
                           pMatrix, this->program, this->wall_placable);
    }

  // draw placable tree
  DrawGL::draw_if_true(this->tree, vMatrix, Pos,
                       this->rotation, QVector3D(1, 1, 1),
                       this->textures.value(3),
                       QVector3D(), QVector2D(1, 1),
                       pMatrix, this->program,
                       this->tree_placable);

  // draw placable floorplan
  DrawGL::draw_if_true(this->plane, vMatrix, Pos,
                       this->rotation, this->currentscale,
                       this->textures_from_files.
                       value(this->textures_from_files.count() - 1),
                       QVector3D(), QVector2D(1, 1), pMatrix,
                       this->program, this->placable_floor_plan
                       && (this->textures_from_files.count() > 0));

  // draw all the nodes here
  foreach(Node *n, this->nodes) {
    QMatrix4x4 translation;
    translation.translate(n->Position());
    if ( n->getSignificant())
      DrawGL::DrawModel(this->node, vMatrix,
                        translation, QMatrix4x4(),
                        this->textures.value(0),
                        QVector3D(1, 0, 0),
                        QVector2D(1, 1),
                        this->program, pMatrix);
    else
        DrawGL::DrawModel(this->node, vMatrix,
                          translation, QMatrix4x4(),
                          this->textures.value(0),
                          QVector3D(), QVector2D(1, 1),
                          this->program, pMatrix);
  }

    // draw all the node lines here
    foreach(Node *n, this->nodes) {
        if ( n->Position().distanceToPoint(Pos) < 0.5 ) {
            // draw red circle to indicate the node will be removed
            if ( this->node_removable)
            draw_circle_flat(n->Position(), vMatrix, QVector3D(1, 0, 0), 0.7f);

            // draw green circle to indicate a link will be added
            if ( this->node_linkable)
            draw_circle_flat(n->Position(), vMatrix, QVector3D(0, 1, 0), 0.7f);
        }
        if ( n->Position().distanceToPoint(*this->clicked_position) < 0.5 ) {
            // draw green circle to indicate a link will be added
            if ( this->node_linkable)
            draw_circle_flat(n->Position(), vMatrix, QVector3D(0, 1, 0), 0.7f);
        }
        for ( int i = 0; i  < n->countConnected(); i++ ) {
            if ( n->getConnectedIndex(i) < this->nodes.count() ) {
                QVector3D aux_calc_one, aux_calc_two, aux_angle;
                QMatrix4x4 aux_rotate, aux_45;
                aux_angle = n->Position() -
                            this->
                            nodes.value(n->
                                        getConnectedIndex(i))->
                            Position();
                aux_angle.setY(0);

                // get the angle from the arccos function
                if ( aux_angle.z() > 0 )
                aux_rotate.rotate(45 - 180 *
                                  acos(aux_angle.x() / aux_angle.length()) /
                                  (3.141592),
                                  0,
                                  1,
                                  0);
                else
                  aux_rotate.rotate(45 +
                                    180 *
                                    acos(aux_angle.x() / aux_angle.length()) /
                                    (3.141592),
                                    0,
                                    1,
                                    0);

                aux_45.rotate(90, 0, 1, 0);
                aux_calc_one = aux_rotate * (QVector3D(0, 0, 1));
                aux_calc_two = aux_45 * aux_rotate * (QVector3D(0, 0, 1));

                DrawGL::DrawLine(n->Position(),
                                 this->nodes.value(
                                     n->
                                     getConnectedIndex(i))->
                                 Position(),
                                 vMatrix, QMatrix4x4(),
                                 QMatrix4x4(),
                                 QVector3D(0, 1, 0),
                                 this->program,
                                 pMatrix);
                DrawGL::DrawLine((n->Position() +
                                  this->
                                  nodes.value(n->getConnectedIndex(i))->
                                  Position()) / 2.0,
                                 aux_calc_one +
                                 (n->Position() +
                                  this->
                                  nodes.value(n->getConnectedIndex(i))->
                                  Position()) / 2.0,
                                 vMatrix,
                                 QMatrix4x4(),
                                 QMatrix4x4(),
                                 QVector3D(0, 1, 0),
                                 this->program,
                                 pMatrix);
                DrawGL::DrawLine((n->Position() +
                                  this->
                                  nodes.value(n->getConnectedIndex(i))->
                                  Position()) / 2.0,
                                  aux_calc_two +
                                 (n->Position() +
                                  this->
                                  nodes.value(n->getConnectedIndex(i))->
                                  Position()) / 2.0,
                                 vMatrix,
                                 QMatrix4x4(),
                                 QMatrix4x4(),
                                 QVector3D(0, 1, 0),
                                 this->program,
                                 pMatrix);
            }
        }
    }

    // draw lines last
    foreach(VisualObject *object, this->models) {
        if ( (this->tree_removable)
             && (object->getType().compare("Tree", Qt::CaseInsensitive) == 0)
             && (object->getTranslation().distanceToPoint(Pos) < 4.0) ) {
            // draw a circle here
            draw_circle_flat(object->getTranslation(),
                             vMatrix,
                             QVector3D(1, 0, 0),
                             4.0f);
        }
        if ( this->wall_placable ) {
            if ( object->getLMidHorisontal().distanceToPoint(Pos) < 0.25f )
                draw_circle_flat(object->getLMidHorisontal(),
                                 vMatrix,
                                 QVector3D(0, 1, 0),
                                 0.25f);
            if ( object->getUMidHorisontal().distanceToPoint(Pos) < 0.25f )
                draw_circle_flat(object->getUMidHorisontal(),
                                 vMatrix,
                                 QVector3D(0, 1, 0),
                                 0.25f);
        }
    }
    // draw line if right clicked
    if ( this->mousedown_right )
    DrawGL::DrawLine(*this->clicked_position,
                     *this->current_position,
                     vMatrix, QMatrix4x4(),
                     QMatrix4x4(),
                     QVector3D(0, 1, 0),
                     this->program,
                     pMatrix);

    // draw left clicked line(s)
    if ( (this->node_linkable)
         && (this->mousedown_left)
         && (this->node_index_selected > -1)
         && (this->node_index_selected < this->nodes.count()) ) {
        QVector3D aux_calc_one, aux_calc_two, aux_angle;
        QMatrix4x4 aux_rotate, aux_45;
        aux_angle = this->
                nodes.value(this->node_index_selected)->Position() -
                *this->current_position;
        aux_angle.setY(0);

        // get the angle from the arccos function
        if ( aux_angle.z() > 0 )
        aux_rotate.rotate(45 -
                          180 *
                          acos(aux_angle.x() / aux_angle.length()) /
                          (3.141592),
                          0,
                          1,
                          0);
        else
          aux_rotate.rotate(45 +
                            180 *
                            acos(aux_angle.x() / aux_angle.length()) /
                            (3.141592),
                            0,
                            1,
                            0);

        aux_45.rotate(90, 0, 1, 0);
        aux_calc_one = aux_rotate*(QVector3D(0, 0, 1));
        aux_calc_two = aux_45*aux_rotate*(QVector3D(0, 0, 1));

        DrawGL::DrawLine(this->
                         nodes.value(this->node_index_selected)->
                         Position(),
                         *this->current_position,
                         vMatrix,
                         QMatrix4x4(),
                         QMatrix4x4(),
                         QVector3D(1, 1, 0),
                         this->program,
                         pMatrix);
        DrawGL::DrawLine((this->
                          nodes.value(this->node_index_selected)->
                          Position() +
                          *this->current_position) / 2.0,
                          aux_calc_one +
                          (this->
                          nodes.value(this->node_index_selected)->
                          Position() +
                          *this->current_position) / 2.0,
                          vMatrix,
                          QMatrix4x4(),
                          QMatrix4x4(),
                          QVector3D(1, 1, 0),
                          this->program,
                          pMatrix);
        DrawGL::DrawLine((this->
                          nodes.value(this->node_index_selected)->
                          Position() +
                          *this->current_position) / 2.0,
                          aux_calc_two +
                          (this->
                          nodes.value(this->node_index_selected)->
                          Position() +
                          *this->current_position) / 2.0,
                          vMatrix,
                          QMatrix4x4(),
                          QMatrix4x4(),
                          QVector3D(1, 1, 0),
                          this->program,
                          pMatrix);
    }

    // release the program for this frame
    this->program->release();
    // disable the cullmode for the frame
    glDisable(GL_CULL_FACE);
    // disable the depthtest for the frame
    glDisable(GL_DEPTH_TEST);
    // finish up the opengl frame
    glFinish();

  // draw the text to the scene
  QPainter painter;
  painter.begin(this);
  painter.setPen(Qt::white);
  painter.setFont(QFont("Arial", 8));
  painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
  // draw all the nodes here
  foreach(Node *n, this->nodes) {
    QPoint pos_x_y =
            Mathematics::transform_3d_to_2d(vMatrix, pMatrix,
                                            n->Position(), this->width(),
                                            this->height());
    painter.drawText(pos_x_y.x(), pos_x_y.y(), n->getName());
  }
  painter.end();
}

void RenderState::draw_circle_flat(QVector3D center,
                                   QMatrix4x4 wvp,
                                   QVector3D color,
                                   float radius) {
    const int slices = 36;
    for ( int k = 0; k < slices; k++ ) {
        DrawGL::DrawLine(
                    radius * QVector3D(cos(2 * 3.14 * k / slices),
                    0,
                    sin(2 * 3.14 * k / slices)) + center,
                    radius * QVector3D(cos(2 * 3.14 * (k + 1) / slices),
                    0,
                    sin(2 * 3.14 * (k + 1) / slices)) + center,
                    wvp,
                    QMatrix4x4(),
                    QMatrix4x4(),
                    color,
                    this->program,
                    pMatrix);
    }
}

void RenderState::LoadTextures(QString path) {
  // clear the premises when not empty
  if ( this->textures_from_files.count() > 0 ) {
    this->textures_from_files.clear();
    this->texture_paths.clear();
  }
  /* populate the textures from the text file */
  if ( PremisesExporter::fileExists(path + QString("textures.tl")) ) {
    // load the text file
    QFile textfile(path + QString("textures.tl"));
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
          QString texture_path = "";

          // texture type
          texture_path = list[2];
          QStringList ls = texture_path.split("/");

          // texture index
          QTextStream(&list[1]) >> texture_index;
          QString new_path = path + ls[ls.count()-1];
          load_texture_from_file(new_path);
        }

      // read next line
      line = ascread.readLine();
      }

      // close the textfile
      textfile.close();
    }
  }
}

void RenderState::LoadObjects(QString path) {
    // clear the premises when not empty
    if ( this->models.count() > 0)
        this->models.clear();

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
            /* n-> node
             * j-> join
             */
            if ( list[0] == "o" ) {
                // this is only x, y, z coordinates for the node
                float matrix[9];
                int texture_index = 0;
                QString Type ="";

                // populate the vertices
                for ( int i = 0; i < 9; i++ )
                     QTextStream(&list[i+3]) >> matrix[i];

                // texture index
                QTextStream(&list[12]) >> texture_index;

                // object type
                QTextStream(&list[2]) >> Type;

                // add floorplan
                if ( Type.compare("FloorPlan", Qt::CaseInsensitive) == 0 ) {
                    if ( texture_index < this->textures_from_files.count() ) {
                      VisualObject *object =
                        new VisualObject(this->plane,
                                         this->
                                         textures_from_files[texture_index],
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
                    object->setTextureID(texture_index);
                    this->models.push_back(object);
                    } else {
                      QMessageBox::warning(
                                  this,
                                  tr("Texture file error"),
                                  tr("The texture file may be corrupted\n"
                                  "or the textures are not located in the "
                                  "same folder as the environment file."));
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

void RenderState::LoadNodes(QString filename) {
    // clear the premises when not empty
    if ( this->nodes.count() > 0 )
        this->nodes.clear();

    /* populate the premisis from the text file */

    // load the text file
    QFile textfile(filename + QString("nodes.pvc"));

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
            /* n-> node
             * j-> join
             */
            if ( list[0] == "n" ) {
                // this is only x, y, z coordinates for the node
                float vertex[3];
                int signi = 0;
                QString display_name ="";
                // populate the vertices
                for ( int i = 0; i < 3; i++ )
                     QTextStream(&list[i+2]) >> vertex[i];

                // get node significance
                QTextStream(&list[6]) >> signi;
                // get the node's name
                display_name = list[5];
                Node* n = new Node(new QVector3D(vertex[0],
                                                 vertex[1],
                                                 vertex[2]));
                // set node's significance
                n->setSignificant((signi == 1));
                // set node's name
                n->setName(display_name);
                // add the node to the premises
                this->nodes.push_back(n);

            } else if ( list[0] == "j" ) {
                   // this is only the indices that should be join
                    int uv[2];

                    // populate the indices
                    for ( int i = 0; i < 2; i++ )
                         QTextStream(&list[i+1]) >> uv[i];

                    QString p = this->nodes.value(uv[1])->getName();
                    // add the links
                    this->nodes.value(uv[0])->AddLink(&p, uv[1]);
             }
            // read next line
           line = ascread.readLine();
        }

        // close the textfile
        textfile.close();
    }
}

RenderState::~RenderState() {
  delete this->program;
  delete this->position;
  delete this->clicked_position;
  delete this->node;
  delete this->plane;
  delete this->wall;
  delete this->door;
  delete this->tree;
  delete this->current_position;
}
