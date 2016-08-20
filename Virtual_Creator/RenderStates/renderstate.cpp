/* Copyright 2015 Ruan Luies */

#include <algorithm>
#include <QDir>
#include <QtXml>
#include "./renderstate.h"
#include "Functions/mathematics.h"

RenderState::RenderState(QWidget *parent): QOpenGLWidget(parent),
  program(0),mouse_x(0),
  mouse_y(0),node_index_selected(-1),
  mouse_zoom(60.0f),noderadius(0.5f),
  mouse_y_inverted(1.0f),current_floor_height(0.0f),
  position_camera(QVector3D()),camera_prev(QVector3D()),
  raycast(QVector3D()),rotation(QVector3D()),
  currentscale(QVector3D(1, 1, 1)),drag_middle_position(QVector3D()),
  mousedown_right(false),mousedown_left(false),node_placable(false),
  node_significant(true),edit_node(false),tree_radius(4.0f),
  infinte_lenght_lines(100.0f), w_edge(0.0),key_ctl(false), snap_grid(false){
  this->link_removable = false;
  this->node_removable = false;
  // enable antialiasing (set the format of the widget)
  QSurfaceFormat format;
  format.setSamples(4);
  this->setFormat(format);

  // initialize the clicked position
  this->clicked_position = new QVector3D(-4445.3,-3455,-345555);

  // set the current mouse position in 3D
  this->current_position = new QVector3D(0,-2033,-93345);


  // set the position to initial null vector
  this->position = new QVector3D();

  // clear the nodes
  this->nodes.clear();

  // set mouse tracking
  setMouseTracking(true);

  // add focus for the keyboard
  setFocusPolicy(Qt::StrongFocus);

  // initialized successfully
  emit debug_results("Premises Visualizer Initialized");

}

void RenderState::receive_edit_edge(bool edit) {
  this->edit_edge = edit;
}

void RenderState::receive_snap_to_grid(bool snap) {
  this->snap_grid = snap;
}

void RenderState::allow_edit_node(bool allow) {
  this->edit_node = allow;
}

void RenderState::allow_node(bool value) {
  this->node_placable = value;
  if ( value )
    this->node_index_selected = -1;
}

void RenderState::allow_remove_link(bool allow) {
  this->link_removable = allow;
}

void RenderState::invert_mouseY(bool value) {
  if (value)
    this->mouse_y_inverted = -1.0f;
  else
    this->mouse_y_inverted = 1.0f;
}

void RenderState::set_next_node_name(QString value) {
  this->next_node_name = value;
  if ( this->node_index_selected < this->nodes.count() &&
       this->node_index_selected > -1 )
    nodes.value(this->node_index_selected)->setName(value);

}

void RenderState::set_next_node_significant(bool value) {
  this->node_significant = value;
  if ( this->node_index_selected > -1 &&
       this->edit_node &&
       this->node_index_selected < this->nodes.count() )
    nodes.value(this->node_index_selected)->setSignificant(value);

}

void RenderState::allow_remove_node(bool value) {
  this->node_removable = value;
}

void RenderState::allow_link(bool value) {
  this->node_linkable = value;
}

void RenderState::change_current_floor_height(float value) {
  this->current_floor_height = value;
  // update the opengl widget
  update();
}

void RenderState::initializeGL() {
  initializeOpenGLFunctions();
}
void RenderState::keyPressEvent(QKeyEvent* event) {
  if(event->key() == Qt::Key_Control) {
      this->key_ctl = true;
    }
}

void RenderState::keyReleaseEvent(QKeyEvent* event) {
  if(event->key() == Qt::Key_Control) {
      this->key_ctl = false;
    }
}

void RenderState::mouseMoveEvent(QMouseEvent* event) {
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
                                             this->vMatrix, pMatrix);

  if ( this->mousedown_right && this->key_ctl) {
      this->position_camera.setX(this->clicked_position->x() -
                                 this->current_position->x());
      this->position_camera.setY(this->clicked_position->y() -
                                 this->current_position->y());
      this->position_camera.setZ(this->clicked_position->z() -
                                 this->current_position->z());

      // pan view
      this->camera_prev.setX(this->camera_prev.x() -
                             this->position_camera.x() * 0.5);
      this->camera_prev.setY(this->camera_prev.y() -
                             this->position_camera.y() * 0.5);
      this->camera_prev.setZ(this->camera_prev.z() -
                             this->position_camera.z() * 0.5);
      this->position_camera = QVector3D(0, 0, 0);
    }

  // removable dragable nodes
  if ( this->mousedown_left && this->node_removable ) {
      remove_nodes();
    }

  // when node can be edited, allow movement
  if (this->mousedown_right && this->edit_node &&
      !(this->edit_edge || this->link_removable || this->node_linkable)) {
      edit_node_position(QVector2D(this->current_position->x(), this->current_position->z()));
      if (this->node_index_selected > 0 && this->node_index_selected < this->nodes.count())
        send_edit_node(this->nodes.value(this->node_index_selected)->getName(),
                       QVector2D(this->nodes.value(this->node_index_selected)->Position().x(),
                                 this->nodes.value(this->node_index_selected)->Position().z()));
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

          // update errors
          update_node_errors();
        }


    }

  this->clicked_position = new QVector3D(0, -1000, 0);
  this->rotation = QVector3D();
  // this->currentscale = QVector3D(1, 1, 1);
  // update the frame
  update();
}

void RenderState::edit_node_position(QVector2D position) {
  if ( this->node_index_selected > -1 &&
       this->edit_node &&
       this->node_index_selected < this->nodes.count() )
    nodes.value(this->node_index_selected)->setPosition(
          QVector3D(position.x(),
                    nodes.value(this->node_index_selected)->Position().y(),
                    position.y()));



}
void RenderState::receive_edge_weight(double w_edge) {
  this->w_edge = w_edge;
}

void RenderState::mousePressEvent(QMouseEvent* event) {
  // make dragable from left click
  if ( event->button() == Qt::LeftButton)
    this->mousedown_left = true;

  // right click to move the camara around
  if ( event->button() == Qt::RightButton) {
      this->mousedown_right = true;
      // if ( !this->edit_node )
      // this->node_index_selected = -1;
    }

  // left click to add the node
  if ( (event->button() == Qt::LeftButton) && (this->node_placable) ) {
      QVector3D Pos = *this->current_position;
      if (this->snap_grid) {
          Pos.setX(qRound(Pos.x()));
          Pos.setZ(qRound(Pos.z()));
        }
      add_node(new QString(this->next_node_name), Pos, QVector3D(0, 0, 0));

    }


  // set current clicked position
  this->clicked_position = new QVector3D(this->current_position->x(),
                                         this->current_position->y(),
                                         this->current_position->z());

  // left click to remove the node
  if ( (event->button() == Qt::LeftButton) && (this->node_removable) ) {
      remove_nodes();
    }



  // left click to remove the link
  if ( (event->button() == Qt::LeftButton) && (this->link_removable) ) {
      remove_link();
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

  // left click to edit the node
  if ( (event->button() == Qt::LeftButton) && (this->edit_node) ) {
      // get position of the clicked
      this->clicked_position = new QVector3D(this->current_position->x(),
                                             this->current_position->y(),
                                             this->current_position->z());
      // collision detection
      for ( int l = 0; l < this->nodes.count(); l++ ) {
          if ( this->clicked_position->
               distanceToPoint(this->nodes.value(l)->Position()) < this->noderadius) {
              this->node_index_selected = l;
              send_edit_node(this->nodes.value(l)->getName(),
                             QVector2D(this->nodes.value(l)->Position().x(),
                                       this->nodes.value(l)->Position().z()));
              emit debug_results("Selected node index:" + QString::number(l));
            }
        }
    }
}

void RenderState::remove_link() {
  // remove link
  for ( int k = 0; k < this->nodes.count(); k++ ) {
      const unsigned int count_connected =
          this->nodes.value(k)->countConnected();
      QVector3D node_position_current = this->nodes.value(k)->Position();
      // remove all the links of the deleted node
      for ( unsigned int z = 0; z < count_connected; z++ ) {
          int connected_index = this->nodes.value(k)->getConnectedIndex(z);
          QVector3D alt_node_position =
              this->nodes.value(connected_index)->Position();
          if ( Mathematics::detect_point_near_line(node_position_current,
                                                   alt_node_position,
                                                   QVector3D(this->current_position->x(),
                                                             this->current_position->y(),
                                                             this->current_position->z()),
                                                   0.25) ) {
              this->nodes.value(k)->RemoveLinkedFromIndex(z);
            }
        }
    }
  // update errors
  update_node_errors();



}


void RenderState::remove_nodes() {
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


  // show node errors
  update_node_errors();
}

void RenderState::wheelEvent(QWheelEvent* event) {
  // camera zoom with the mouse scroll
  this->mouse_zoom -= static_cast<float>(event->delta()) / 120.0f;

  // limit the zoom
  if ( this->mouse_zoom < 2.0f)
    this->mouse_zoom = 2.0f;

  // update the openGL frame after the zoom
  update();
}

void RenderState::update_node_errors() {
  // add nodes for debugging
  error_nodes.clear();


  for ( int i = 0; i < error_nodes.count(); i++ ) {
      if (error_nodes.value(i) < 0 && error_nodes.value(i) > this->nodes.count()) {
          error_nodes.remove(i);
        }
    }
}

void RenderState::add_node(QString* name, QVector3D positon, QVector3D colour) {
  // create new nodes
  Node *newnode = new Node(new QVector3D(positon.x(),
                                         positon.y(),
                                         positon.z()),
                           name);
  // set significance
  newnode->setSignificant(this->node_significant);

  // set colour
  newnode->setColor(new QVector3D(colour));
  // add new node to vector
  this->nodes.push_back(newnode);

  // show node errors
  update_node_errors();

}


void RenderState::resizeGL(int w, int h) {
  // setup the viewport for opengl
  glViewport(0, 0, w, h);

  // initialize the projection matrix
  pMatrix.setToIdentity();

  // set the projection matrix
  pMatrix.perspective(10,
                      static_cast<float>(w) /
                      static_cast<float>(h),
                      1.0f,
                      1000.0f);
}

void RenderState::LoadContent() {
  // this initializes all the opengl functions
  initializeOpenGLFunctions();

  // load meshes
  this->node = new ModelMesh("://Sphere");
  // load texture for nodes
  this->texture = new QOpenGLTexture(QImage("://Texture0"));
  this->texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
  this->texture->setMagnificationFilter(QOpenGLTexture::Linear);

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
  this->vMatrix.setToIdentity();
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
  QVector3D cameraPosition = cameraTransformation *
      QVector3D(0,
                0,
                this->mouse_zoom +
                this->current_floor_height);
  // define the direction of the camera's up vector

  QVector3D cameraUpDirection = cameraTransformation *
      QVector3D(0, 1, 0);
  // implement and transform the camera
  this->vMatrix.lookAt(cameraPosition,
                       QVector3D(0,
                                 this->current_floor_height,
                                 0),
                       cameraUpDirection);
  this->vMatrix.translate(this->camera_prev);
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
  if (this->snap_grid) {
      Pos.setX(qRound(Pos.x()));
      Pos.setZ(qRound(Pos.z()));
    }

  // draw placable objects here
  draw_placable_items(Pos);
  // draw all the nodes here
  draw_nodes();
  // draw all the lines connected to nodes with directional arrows
  draw_node_lnes(Pos);

  // draw left clicked line(s)
  if ( (this->node_linkable) &&
       (this->mousedown_left) &&
       (this->node_index_selected > -1) &&
       (this->node_index_selected < this->nodes.count()) ) {
      QVector3D aux_calc_one, aux_calc_two, aux_angle;
      QMatrix4x4 aux_rotate, aux_45;
      aux_angle = this->nodes.value(this->node_index_selected)->Position() -
          *this->current_position;
      aux_angle.setY(0);

      // get the angle from the arccos function
      if ( aux_angle.z() > 0 ) {
          aux_rotate.rotate(45 - 180 *  acos(aux_angle.x() / aux_angle.length()) /
                            (3.141592), 0, 1, 0);
        } else {
          aux_rotate.rotate(45 + 180 * acos(aux_angle.x() / aux_angle.length()) /
                            (3.141592), 0, 1, 0);
        }
      aux_45.rotate(90, 0, 1, 0);
      aux_calc_one = aux_rotate*(QVector3D(0, 0, 1));
      aux_calc_two = aux_45*aux_rotate*(QVector3D(0, 0, 1));

      DrawGL::DrawLine(this->nodes.value(this->node_index_selected)->Position(),
                       *this->current_position, this->vMatrix,
                       QMatrix4x4(), QMatrix4x4(), QVector3D(1, 1, 0),
                       this->program, pMatrix, this->current_floor_height);
      DrawGL::DrawLine((this-> nodes.value(this->node_index_selected)->
                        Position() +  *this->current_position) / 2.0,
                       aux_calc_one + (this->nodes.value(
                                         this->node_index_selected)->
                                       Position() +
                                       *this->current_position) / 2.0,
                       this->vMatrix, QMatrix4x4(), QMatrix4x4(),
                       QVector3D(1, 1, 0), this->program, pMatrix,
                       this->current_floor_height);
      DrawGL::DrawLine((this->nodes.value(this->node_index_selected)->
                        Position() + *this->current_position) / 2.0,
                       aux_calc_two +
                       (this->nodes.value(this->node_index_selected)->
                        Position() + *this->current_position) / 2.0,
                       this->vMatrix, QMatrix4x4(), QMatrix4x4(),
                       QVector3D(1, 1, 0), this->program, pMatrix,
                       this->current_floor_height);
    }
  // release the program for this frame
  this->program->release();
  // disable the cullmode for the frame
  glDisable(GL_CULL_FACE);
  // disable the depthtest for the frame
  glDisable(GL_DEPTH_TEST);
  // finish up the opengl frame
  glFinish();

  // draw the node text to the scene
  draw_node_names();
}

void RenderState::draw_placable_items(QVector3D Pos) {
  // draw placable node
  DrawGL::draw_if_true(this->node, this->vMatrix,
                       Pos, this->rotation,
                       QVector3D(0.51,0.51,0.51),
                       this->texture,
                       QVector3D(1, 0, 0),
                       QVector2D(1, 1),
                       pMatrix, this->program,
                       this->node_placable
                       && this->node_significant,
                       this->current_floor_height);

  // draw placable node (not significant)
  DrawGL::draw_if_true(this->node, this->vMatrix,
                       Pos, this->rotation,
                       QVector3D(0.5, 0.5, 0.5),
                       this->texture,
                       QVector3D(), QVector2D(1, 1),
                       pMatrix, this->program,
                       this->node_placable
                       && !this->node_significant,
                       this->current_floor_height);




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
                       this->vMatrix, QMatrix4x4(), QMatrix4x4(),
                       QVector3D(1, 1, 1), this->program, pMatrix,
                       this->current_floor_height);
    }
  this->currentscale.setZ(this->clicked_position->
                          distanceToPoint(*this->current_position));

}

void RenderState::draw_node_names() {
  // draw the nodes to the scene
  QPainter painter;
  painter.begin(this);
  painter.setPen(Qt::white);
  painter.setFont(QFont("Arial", 8));
  //painter.setRenderHints(QPainter::Antialiasing |
  //                        QPainter::SmoothPixmapTransform);
  // draw all the node text here
  foreach(Node *n, this->nodes) {
      if ( ( n->Position().y() < this->current_floor_height + 0.5 ) &&
           ( n->Position().y() > this->current_floor_height - 0.5 ) ) {
          QPoint pos_x_y =
              Mathematics::transform_3d_to_2d(this->vMatrix, this->pMatrix,
                                              n->Position(), this->width(),
                                              this->height());
          painter.drawText(pos_x_y.x(), pos_x_y.y(), n->getName());
        }
    }
  painter.end();
}

void RenderState::draw_nodes() {

  // draw all the nodes here
  foreach(Node *n, this->nodes) {
      QMatrix4x4 translation;
      translation.translate(n->Position());
      translation.scale(0.5);
      DrawGL::DrawModel(this->node, this->vMatrix,
                        translation, QMatrix4x4(),
                        this->texture,
                        n->getColor(), QVector2D(1, 1),
                        this->program, this->pMatrix,
                        this->current_floor_height);

    }
}

void RenderState::clear_premises() {
  // clear the nodes
  this->nodes.clear();
}

void RenderState::draw_node_lnes(QVector3D Pos) {
  // draw all the node lines here
  foreach(Node *n, this->nodes) {
      if ( n->Position().distanceToPoint(Pos) < 0.5 ) {
          // draw red circle to indicate the node will be removed
          if ( this->node_removable)
            draw_circle_flat(n->Position(), this->vMatrix,
                             QVector3D(1, 0, 0), 0.7f);

          // draw green circle to indicate a link will be added
          if ( this->node_linkable)
            draw_circle_flat(n->Position(), this->vMatrix,
                             QVector3D(0, 1, 0), 0.7f);

          // draw green circle to indicate a link will be added
          if ( this->edit_node )
            draw_circle_flat(n->Position(), this->vMatrix,
                             QVector3D(1, 0.5, 0.25), 0.7f);
        }
      if ( n->Position().distanceToPoint(*this->clicked_position) < 0.5 ) {
          // draw green circle to indicate a link will be added
          if ( this->node_linkable)
            draw_circle_flat(n->Position(), this->vMatrix,
                             QVector3D(0, 1, 0), 0.7f);
        }
      for ( int i = 0; i  < n->countConnected(); i++ ) {
          QVector3D color = QVector3D(0, 1, 0);
          if ( Mathematics::detect_point_near_line(n->Position(),
                                                   this->nodes.value(n->getConnectedIndex(i))->Position(),
                                                   QVector3D(this->current_position->x(),
                                                             this->current_position->y(),
                                                             this->current_position->z()),
                                                   0.5) &&
               this->link_removable) {
              color = QVector3D(1, 0, 0);
            } else {
              color = QVector3D(0, 1, 0);
            }
          if ( n->getConnectedIndex(i) < this->nodes.count() ) {
              QVector3D aux_calc_one, aux_calc_two, aux_angle;
              QMatrix4x4 aux_rotate, aux_45;
              aux_angle = n->Position() -
                  this->nodes.value(n->getConnectedIndex(i))->Position();
              aux_angle.setY(0);

              // get the angle from the arccos function
              if ( aux_angle.z() > 0 ) {
                  aux_rotate.rotate(45 - 180 *
                                    acos(aux_angle.x() / aux_angle.length()) /
                                    (3.141592),
                                    0,
                                    1,
                                    0);
                } else {
                  aux_rotate.rotate(45 +
                                    180 *
                                    acos(aux_angle.x() / aux_angle.length()) /
                                    (3.141592),
                                    0,
                                    1,
                                    0);
                }

              aux_45.rotate(90, 0, 1, 0);
              aux_calc_one = aux_rotate * (QVector3D(0, 0, 0.25));
              aux_calc_two = aux_45 * aux_rotate * (QVector3D(0, 0, 0.25));

              DrawGL::DrawLine(n->Position(),
                               this->nodes.value(
                                 n->getConnectedIndex(i))->Position(),
                               this->vMatrix, QMatrix4x4(), QMatrix4x4(),
                               color, this->program, pMatrix,
                               this->current_floor_height);
              DrawGL::DrawLine((n->Position() +
                                this->nodes.value(n->getConnectedIndex(i))->
                                Position()) / 2.0,
                               aux_calc_one +
                               (n->Position() +
                                this->nodes.value(n->getConnectedIndex(i))->
                                Position()) / 2.0,
                               this->vMatrix, QMatrix4x4(), QMatrix4x4(),
                               color, this->program, pMatrix,
                               this->current_floor_height);
              DrawGL::DrawLine((n->Position() +
                                this->nodes.value(n->getConnectedIndex(i))->
                                Position()) / 2.0,
                               aux_calc_two +
                               (n->Position() +
                                this->nodes.value(n->getConnectedIndex(i))->
                                Position()) / 2.0,
                               this->vMatrix, QMatrix4x4(), QMatrix4x4(),
                               color, this->program, pMatrix,
                               this->current_floor_height);
            }
        }
    }
}

void RenderState::add_edge(int source, int target, double weight) {
  nodes.value(source)->AddLink(new QString("s"), target);
}

void RenderState::draw_circle_flat(QVector3D center,
                                   QMatrix4x4 wvp,
                                   QVector3D color,
                                   float radius) {
  const int slices = 6;
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
            pMatrix, this->current_floor_height);
    }
}
QString RenderState::read_string_from_line(QString name, QString string, int start) {
  int pos_id = string.indexOf(name, start, Qt::CaseInsensitive);
  int pos_id_1 = string.indexOf("\"", pos_id, Qt::CaseInsensitive);
  int pos_id_2 = string.indexOf("\"", pos_id_1 + 1, Qt::CaseInsensitive);
  return string.mid(pos_id_1 + 1, pos_id_2 - pos_id_1 - 1);
}

void RenderState::load_new_graph(QString filename) {
  this->nodes.clear();
  QFile xml_file(filename);
  if(!xml_file.open(QIODevice::ReadOnly)) {
      QMessageBox::information(0, "error", xml_file.errorString());
    }
  QXmlStreamReader xml_reader(&xml_file);

  // data needed to build graph
  QString name ="";
  QVector3D position(0, 0, 0);
  QVector3D rgb(0, 0, 0);
  int id = -1;

  //Parse the XML until we reach end of it
  while(!xml_reader.atEnd() && !xml_reader.hasError()) {
      // Read next element
      QXmlStreamReader::TokenType token = xml_reader.readNext();
      //If token is just StartDocument - go to next
      if(token == QXmlStreamReader::StartDocument) {
          continue;
        }
      if(token == QXmlStreamReader::EndElement) {
          if(xml_reader.name() == "node") {
              add_node(new QString(name), position, rgb);
              name ="";
              position = QVector3D(0, 0, 0);
              rgb = QVector3D(0, 0, 0);
            }
        }
      //If token is StartElement - read it
      if(token == QXmlStreamReader::StartElement) {
          if(xml_reader.name() == "nodes") {
              continue;
            }
          if(xml_reader.name() == "node") {
              foreach (QXmlStreamAttribute a, xml_reader.attributes().toList()) {
                  if (a.name() == "label") {
                      name = a.value().toString();
                    } else if (a.name() == "id") {
                      id = a.value().toInt();
                    } else if (a.name() == "x") {
                      position.setX(a.value().toFloat());
                    } else if (a.name() == "y") {
                      position.setZ(a.value().toFloat());
                    } else if (a.name() == "z") {
                      position.setY(a.value().toFloat());
                    } else if (a.name() == "r") {
                      rgb.setX(a.value().toFloat() / 255.0);
                    } else if (a.name() == "g") {
                      rgb.setY(a.value().toFloat() / 255.0);
                    } else if (a.name() == "b") {
                      rgb.setZ(a.value().toFloat() / 255.0);
                    }
                }
              continue;
            }
          if(xml_reader.name() == "position") {
              foreach (QXmlStreamAttribute a, xml_reader.attributes().toList()) {
                  if (a.name() == "x") {
                      position.setX(a.value().toFloat());
                    } else if (a.name() == "y") {
                      position.setZ(a.value().toFloat());
                    } else if (a.name() == "z") {
                      position.setY(a.value().toFloat());
                    }
                }
            }
          if(xml_reader.name() == "color") {
              foreach (QXmlStreamAttribute a, xml_reader.attributes().toList()) {
                  if (a.name() == "r") {
                      rgb.setX(a.value().toFloat() / 255.0);
                    } else if(a.name() == "g") {
                      rgb.setY(a.value().toFloat() / 255.0);
                    } else if(a.name() == "b") {
                      rgb.setZ(a.value().toFloat() / 255.0);
                    }
                }
            }


          if(xml_reader.name() == "edges") {
              continue;
            }
          if(xml_reader.name() == "edge") {
              QString name ="";
              int source = 0;
              int target = 0;
              double weight = 0.0;

              foreach (QXmlStreamAttribute a, xml_reader.attributes().toList()) {
                  if (a.name() == "label") {
                      name = a.value().toString();
                    } else if (a.name() == "target") {
                      source = a.value().toInt();
                    } else if (a.name() == "source") {
                      target = a.value().toInt();
                    } else if (a.name() == "weight") {
                      weight = a.value().toDouble();
                    }
                }
              add_edge(source, target, weight);
            }
        }
    }

  if(xml_reader.hasError()) {
      QMessageBox::critical(this,
                            ".xml Parse Error", xml_reader.errorString(),
                            QMessageBox::Ok);
      return;
    }

  //close reader and flush file
  xml_reader.clear();
  xml_file.close();
}

RenderState::~RenderState() {
  delete this->program;
  delete this->position;
  delete this->clicked_position;
  delete this->node;
  delete this->texture;
  delete this->current_position;
}
