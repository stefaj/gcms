#include "renderstate.h"
#include "Functions/mathematics.h"

RenderState::RenderState(QWidget *parent): QOpenGLWidget(parent),
    m_program(0),
    m_mouse_x(0),
    m_mouse_y(0),
    m_node_index_selected(-1),
    m_mouse_zoom(60.0f),
    m_noderadius(0.5f),
    m_mouse_y_inverted(1.0f),
    m_current_floor_height(0.0f),
    m_position_camera(QVector3D()),
    m_camera_prev(QVector3D()),
    m_raycast(QVector3D()),
    m_rotation(QVector3D()),
    m_currentscale(QVector3D(1,1,1)),
    m_drag_middle_position(QVector3D()),
    m_corner_1(QVector3D()),
    m_corner_2(QVector3D()),
    m_corner_3(QVector3D()),
    m_corner_4(QVector3D()),
    m_center_h_1(QVector3D()),
    m_center_h_2(QVector3D()),
    m_mousedown_right(false),
    m_mousedown_left(false),
    m_node_placable(false),
    m_pavement_placable(false),
    m_tree_placable(false),
    m_placable_floor_plan(false),
    tree_radius(4.0f),
    infinte_lenght_lines(100.0f){

    // enable antialiasing (set the format of the widget)
    QSurfaceFormat format;
    format.setSamples(4);
    this->setFormat(format);

    // initialize the clicked position
    m_clicked_position = new QVector3D();

    // set the current mouse position in 3D
    m_current_position = new QVector3D();

    // clear the textures
    m_textures.clear();

    // set the position to initial null vector
    m_position = new QVector3D();

    // clear the nodes
    m_nodes.clear();

    // clear visual objects
    m_models.clear();

    // set mouse tracking
    setMouseTracking(true);
}

void RenderState::allow_node(bool value){m_node_placable = value;}

void RenderState::invert_mouseY(bool value){
    if (value)
        m_mouse_y_inverted = -1.0f;
    else
        m_mouse_y_inverted = 1.0f;
}

void RenderState::allow_remove_node(bool value){m_node_removable = value;}

void RenderState::allow_remove_tree(bool value){m_tree_removable = value;}

void RenderState::allow_link(bool value){m_node_linkable = value;}

void RenderState::allow_pavement(bool value){m_pavement_placable = value;}

void RenderState::allow_door(bool value){m_door_placeable = value;}

void RenderState::allow_wall(bool value){m_wall_placable = value;}

void RenderState::allow_tree(bool value){m_tree_placable = value;}

void RenderState::allow_floor_plan(bool value){m_placable_floor_plan = value;}

void RenderState::change_rotY(double value){m_rotation.setY(value);}

void RenderState::set_object_scale(QVector3D value){m_currentscale = value;}

void RenderState::change_current_floor_height(float value){m_current_floor_height=value;}

void RenderState::load_texture_from_file(QString value)
{
    QOpenGLTexture *texture = new QOpenGLTexture(QImage(value).mirrored());
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_textures_from_files.push_back(texture);
}

void RenderState::initializeGL(){
    initializeOpenGLFunctions();
     // texture test
    for(int i = 0;i<5;i++){
    QOpenGLTexture *texture = new QOpenGLTexture(QImage("://Texture"+QString::number(i)).mirrored());
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_textures.push_back(texture);
    }
}

void RenderState::mouseMoveEvent(QMouseEvent *event){

    // alert mouse event's position (x)
    m_mouse_x = event->x();

    // alert mouse event's position (x)
    m_mouse_y = event->y();

    // update raycast vector
    m_raycast = Mathematics::mouse_raycast(m_mouse_x, m_mouse_y, this->width(), this->height(), m_mouse_y_inverted, vMatrix, pMatrix);

    if(m_mousedown_right){
        m_position_camera.setX(m_clicked_position->x()-m_current_position->x());
        m_position_camera.setY(m_clicked_position->y()-m_current_position->y());
        m_position_camera.setZ(m_clicked_position->z()-m_current_position->z());

        // pan view
        m_camera_prev.setX(m_camera_prev.x()-m_position_camera.x());
        m_camera_prev.setY(m_camera_prev.y()-m_position_camera.y());
        m_camera_prev.setZ(m_camera_prev.z()-m_position_camera.z());
        m_position_camera = QVector3D(0,m_current_floor_height,0);
    }

    // removable dragable nodes
    if(m_mousedown_left&&m_node_removable){
        // collision detection
        for(int l = 0;l<m_nodes.count();l++){
            if(m_current_position->distanceToPoint(m_nodes.value(l)->Position())<m_noderadius){
                // remove node
                m_nodes.removeAt(l);
                // remove all dependencies
                for(int i = 0;i<m_nodes.count();i++){
                    for(int z = 0; z<m_nodes.value(i)->countConnected();z++){
                        if(m_nodes.value(i)->getConnectedIndex(z)==l)
                            m_nodes.value(i)->RemoveLinkedFromIndex(z);
                    }
                    // move the link back after the node was deleted
                    for(int k = 0; k<m_nodes.value(i)->countConnected();k++){
                        if(m_nodes.value(i)->getConnectedIndex(k)>l)
                            m_nodes.value(i)->MoveLinkedIndexBack(k);
                    }
                }
            }
        }
    }

    // update openGL widget
    update();
}

void RenderState::mouseReleaseEvent(QMouseEvent *){
    // release button right click
    if(m_mousedown_right)
    m_mousedown_right = false;

    // button left click released
    if(m_mousedown_left){
        m_mousedown_left = false;

        if(m_node_linkable){
            int linkindex = -1;
            // get position of the clicked
            m_clicked_position = new QVector3D(m_current_position->x(),m_current_position->y(),m_current_position->z());

            // collision detection
            for(int l = 0;l<m_nodes.count();l++){
                if(m_clicked_position->distanceToPoint(m_nodes.value(l)->Position())<m_noderadius)
                    linkindex = l;
            }
            if((linkindex>-1)&&(m_node_index_selected>-1)&&(m_node_index_selected<m_nodes.count())){
                // add a link to the node
                m_nodes.value(m_node_index_selected)->AddLink(new QString("Link"+QString::number(m_nodes.value(m_node_index_selected)->countConnected())),linkindex);
            }
            // export to temp nodes
            PremisesExporter::export_nodes(m_nodes,"nodes.pvc");
        }

        if(m_wall_placable){
            // place wall
             add_wall(m_rotation,m_drag_middle_position,m_currentscale);
        }

        if(m_pavement_placable){
            // place pavement
            add_pavement(m_rotation,*m_clicked_position,m_currentscale);

        }
    }

    m_clicked_position = new QVector3D(0,-1000,0);
    m_rotation = QVector3D();
    m_currentscale = QVector3D(1,1,1);
    // update the frame
    update();
}

void RenderState::mousePressEvent(QMouseEvent *event){
    // make dragable from left click
    if(event->button() == Qt::LeftButton)
    m_mousedown_left = true;

    // right click to move the camara around
    if(event->button() == Qt::RightButton)
        m_mousedown_right = true;

    // left click to add the node
    if((event->button() == Qt::LeftButton)&&(m_node_placable))
    {
        add_node(new QString("pewpew"+QString::number(m_nodes.count())));
        PremisesExporter::export_nodes(m_nodes,"nodes.pvc");
    }

    // left click to add door
    if((event->button() == Qt::LeftButton)&&(m_door_placeable))
        add_door(m_rotation,*m_current_position, m_currentscale);

    // add floor plan
    if((event->button() == Qt::LeftButton)&&(m_placable_floor_plan))
        add_floor_plan(m_rotation,*m_current_position, m_currentscale);

    // left click to add wall
    if((event->button() == Qt::LeftButton)&&(m_wall_placable))
        m_clicked_position = new QVector3D(m_current_position->x(), m_current_position->y(), m_current_position->z());

    // left click to add tree
    if((event->button() == Qt::LeftButton)&&(m_tree_placable))
        add_tree(m_rotation,*m_current_position, m_currentscale);


    // set current clicked position
    m_clicked_position = new QVector3D(m_current_position->x(), m_current_position->y(), m_current_position->z());

    if((event->button() == Qt::LeftButton)&&(m_tree_removable)){
        for(int k = 0 ; k < m_models.count();k++){
            if((m_models.value(k)->getType().compare("Tree",Qt::CaseInsensitive)==0)&&(m_models.value(k)->getTranslation().distanceToPoint(*m_current_position)<tree_radius)){
                m_models.removeAt(k);
            }
        }

    }

    // left click to remove the node
    if((event->button() == Qt::LeftButton)&&(m_node_removable)){
        // collision detection
        for(int l = 0;l<m_nodes.count();l++){
            if(m_current_position->distanceToPoint(m_nodes.value(l)->Position())<m_noderadius){
                // remove node
                m_nodes.removeAt(l);

                // remove all dependencies
                for(int i = 0;i<m_nodes.count();i++){
                    // remove all the links of the deleted node
                    for(int z = 0; z<m_nodes.value(i)->countConnected();z++){
                        if(m_nodes.value(i)->getConnectedIndex(z)==l)
                            m_nodes.value(i)->RemoveLinkedFromIndex(z);
                    }

                    // move the links after the node was deleted
                    for(int k = 0; k<m_nodes.value(i)->countConnected();k++){
                        if(m_nodes.value(i)->getConnectedIndex(k)>l)
                            m_nodes.value(i)->MoveLinkedIndexBack(k);
                    }
                }
            }
        }
    }

    // left click to add the link
    if((event->button() == Qt::LeftButton)&&(m_node_linkable)){
        // get position of the clicked
        m_clicked_position = new QVector3D(m_current_position->x(),m_current_position->y(),m_current_position->z());

        // collision detection
        for(int l = 0;l<m_nodes.count();l++){
            if(m_clicked_position->distanceToPoint(m_nodes.value(l)->Position())<m_noderadius)
                m_node_index_selected = l;
        }
    }
}

void RenderState::wheelEvent(QWheelEvent *event){
    // camera zoom with the mouse scroll
    m_mouse_zoom -= (float)event->delta()/120.0f;

    // limit the zoom
    if(m_mouse_zoom<2.0f)
        m_mouse_zoom = 2.0f;

    // update the openGL frame after the zoom
    update();
}

void RenderState::add_node(QString *name){
    // create new nodes
    Node *newnode = new Node(new QVector3D(m_current_position->x(),
                                           m_current_position->y(),
                                           m_current_position->z()),
                                           name);

    // add new node to vector
    m_nodes.push_back(newnode);
}

void RenderState::add_pavement(QVector3D rotation, QVector3D translation, QVector3D scaling){
    // texture index 1 is the tile
    VisualObject * object = new VisualObject(m_plane,m_textures.value(1),translation,rotation, "Pavement");
    object->setScaling(scaling);
    m_models.push_back(object);
}

void RenderState::add_tree(QVector3D rotation, QVector3D translation, QVector3D scaling){
    // texture index 1 is the tile
    VisualObject * object = new VisualObject(m_tree,m_textures.value(2),translation,rotation, "Tree");
    object->setScaling(scaling);
    m_models.push_back(object);
}

void RenderState::add_wall(QVector3D rotation, QVector3D translation, QVector3D scaling){
    // texture index 1 is the tile
    VisualObject * object = new VisualObject(m_wall,m_textures.value(4),translation,rotation, "Wall");
    object->setScaling(scaling);
    // set horizontal centers
    object->setLMidHorisontal(m_center_h_1);
    object->setUMidHorisontal(m_center_h_2);
    m_models.push_back(object);
}

void RenderState::add_door(QVector3D rotation, QVector3D translation, QVector3D scaling){
    // texture index 1 is the tile
    VisualObject * object = new VisualObject(m_door,m_textures.value(2),translation,rotation, "Door");
    object->setScaling(scaling);
    m_models.push_back(object);
}

void RenderState::add_floor_plan(QVector3D rotation, QVector3D translation, QVector3D scaling){
    // texture index 1 is the tile
    VisualObject * object = new VisualObject(m_plane,m_textures_from_files.value(m_textures_from_files.count()-1),translation,rotation, "FloorPlan");
    object->setScaling(scaling);
    m_models.push_back(object);
}

void RenderState::resizeGL(int w, int h){
    // setup the viewport for opengl
    glViewport(0, 0, w, h);

    // initialize the projection matrix
    pMatrix.setToIdentity();

    // set the projection matrix
    pMatrix.perspective(45, (float) w / (float) h, 1.0f, 1000.0f);
}

void RenderState::LoadContent(){

    // this initializes all the opengl functions
    initializeOpenGLFunctions();

    //load meshes
    m_node = new ModelMesh(":/Sphere");
    m_plane = new ModelMesh(":/Plane");
    m_door = new ModelMesh("://DoorWay01");
    m_wall = new ModelMesh("://Wall01");
    m_tree = new ModelMesh("://Tree01");

    // load shaders
    m_program = new QOpenGLShaderProgram();

    // laod vertex shader (the geometry of the 3D objects )
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,"://Vertex");

    // load the pixel/fragment shader. this is the pixel shader (per pixel rendering)
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,"://Fragment");

    // link the shaders
    m_program->link();
}

void RenderState::paintGL(){
    // initialise the view matrix
    vMatrix.setToIdentity();
    // whenever content is not loaded, load the content
    if(!m_program){LoadContent();}
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
    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, m_mouse_zoom) ;
    // define the direction of the camera's up vector
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);
    // implement and transform the camera
    vMatrix.lookAt(cameraPosition, QVector3D(0,m_current_floor_height,0), cameraUpDirection);
    vMatrix.translate(m_camera_prev);

    // return the position of the ray intersection with the y-axis
    QVector3D Pos  = Mathematics::intersectYat(m_raycast, QVector3D(0, m_mouse_zoom, 0)-m_camera_prev ,m_current_floor_height);

    // update current position
    m_current_position->setX(Pos.x());
    m_current_position->setZ(Pos.z());
    m_current_position->setY(Pos.y());

    // draw other objects first
    foreach(VisualObject *object, m_models){
        QMatrix4x4 translation;
        translation.translate(object->getTranslation());
        QMatrix4x4 rotation;
        rotation.rotate(object->getRotation().y(),0,1,0);
        rotation.scale(object->getScaling());
        if(object->getType().compare("FloorPlan")!=0)
        DrawGL::DrawModel(object->getModelMesh(), vMatrix, translation,rotation,object->getTexture(),QVector3D(),QVector2D(object->getScaling().z(),object->getScaling().x()),m_program,pMatrix);
        else
        DrawGL::DrawModel(object->getModelMesh(), vMatrix, translation,rotation,object->getTexture(),QVector3D(),QVector2D(1,1),m_program,pMatrix);

        if(m_wall_placable){
            if(object->getLMidHorisontal().distanceToPoint(Pos)<0.25f)
                *m_current_position = object->getLMidHorisontal();
            if(object->getUMidHorisontal().distanceToPoint(Pos)<0.25f)
               *m_current_position = object->getUMidHorisontal();
        }
    }

    // draw placable node
    DrawGL::draw_if_true(m_node, vMatrix,Pos,m_rotation,QVector3D(1,1,1),m_textures.value(0),QVector3D(),QVector2D(1,1),pMatrix,m_program,m_node_placable);
    // draw placable tile draggable mouse
    DrawGL::draw_if_true(m_plane, vMatrix,Pos,m_rotation,QVector3D(1,1,1),m_textures.value(1),QVector3D(),QVector2D(m_currentscale.z(),m_currentscale.x()),pMatrix,m_program,m_pavement_placable&&(!m_mousedown_left));
    // draw placable tile clicked
    if(m_mousedown_left&&m_pavement_placable){
        m_currentscale.setZ(pow(pow((m_clicked_position->z()-m_current_position->z()),2),0.5)*2.0);
        m_currentscale.setY(1);
        m_currentscale.setX(pow(pow((m_clicked_position->x()-m_current_position->x()),2),0.5)*2.0);
    }
    // draw pavement
    DrawGL::draw_if_true(m_plane, vMatrix,*m_clicked_position,m_rotation,m_currentscale,m_textures.value(1),QVector3D(),QVector2D(m_currentscale.z(),m_currentscale.x()),pMatrix,m_program,m_pavement_placable&&(m_mousedown_left));

    // draw placable door
    DrawGL::draw_if_true(m_door, vMatrix,Pos,m_rotation,QVector3D(1,1,1),m_textures.value(2),QVector3D(),QVector2D(1,1),pMatrix,m_program,m_door_placeable);

    // draw placable wall
    if((m_mousedown_left)&&(m_wall_placable)){
        m_drag_middle_position = (*m_clicked_position+*m_current_position)/2.0;
        m_rotation.setY(Mathematics::flat_angle_from_vectors(*m_clicked_position, *m_current_position)+90);

        // clamp to 0 and 180 degrees
        if((Mathematics::return_near_degree(m_rotation.y())==0.0)||(Mathematics::return_near_degree(m_rotation.y())==180)){
            // set fixed rotation for the rotation
            m_rotation.setY(Mathematics::return_near_degree(m_rotation.y()));

            // set fixed position for the  x - axis
            m_drag_middle_position.setX(m_clicked_position->x());
            m_current_position->setX(m_clicked_position->x());

           DrawGL::DrawLine(*m_clicked_position+QVector3D(0, 0,-infinte_lenght_lines),
                     *m_current_position+QVector3D(0, 0, infinte_lenght_lines),
                     vMatrix, QMatrix4x4(), QMatrix4x4(),
                     QVector3D(1,1,1), m_program, pMatrix);
        }

        // clamp to 270 and 90 degrees
        if((Mathematics::return_near_degree(m_rotation.y())==270)||
           (Mathematics::return_near_degree(m_rotation.y())==90)||
                (Mathematics::return_near_degree(m_rotation.y())==-90)){
        m_rotation.setY(Mathematics::return_near_degree(m_rotation.y()));
        m_drag_middle_position.setZ(m_clicked_position->z());
        m_current_position->setZ(m_clicked_position->z());
        DrawGL::DrawLine(*m_clicked_position+QVector3D(-infinte_lenght_lines, 0, 0),
                 *m_current_position+QVector3D(infinte_lenght_lines, 0, 0),
                 vMatrix, QMatrix4x4(), QMatrix4x4(),
                 QVector3D(1,1,1), m_program, pMatrix);
        }
        // set clickable centers
        m_center_h_1 = *m_current_position;
        m_center_h_2 = *m_clicked_position;

        m_currentscale.setZ(m_clicked_position->distanceToPoint(*m_current_position));
        DrawGL::draw_if_true(m_wall, vMatrix, m_drag_middle_position, m_rotation, m_currentscale, m_textures.value(4),QVector3D(),QVector2D(m_currentscale.z(),1.0),pMatrix,m_program,m_wall_placable);
    }
    // draw placable tree
    DrawGL::draw_if_true(m_tree, vMatrix,Pos,m_rotation,QVector3D(1,1,1), m_textures.value(3),QVector3D(),QVector2D(1,1),pMatrix,m_program,m_tree_placable);

    // draw placable floorplan
    DrawGL::draw_if_true(m_plane, vMatrix,Pos,m_rotation,m_currentscale, m_textures_from_files.value(m_textures_from_files.count()-1),QVector3D(),QVector2D(1,1),pMatrix,m_program,m_placable_floor_plan&(m_textures_from_files.count()>0));

    // draw all the nodes here
    foreach(Node *n, m_nodes){
        QMatrix4x4 translation;
        translation.translate(n->Position());
        DrawGL::DrawModel(m_node, vMatrix, translation,QMatrix4x4(),m_textures.value(0),QVector3D(),QVector2D(1,1),m_program,pMatrix);
    }

    // draw all the node lines here
    foreach(Node *n, m_nodes){
        if(n->Position().distanceToPoint(Pos)<0.5){
            // draw red circle to indicate the node will be removed
            if(m_node_removable)
            draw_circle_flat(n->Position(),vMatrix,QVector3D(1,0,0),0.7f);

            // draw green circle to indicate a link will be added
            if(m_node_linkable)
            draw_circle_flat(n->Position(),vMatrix,QVector3D(0,1,0),0.7f);
        }
        if(n->Position().distanceToPoint(*m_clicked_position)<0.5){
            // draw green circle to indicate a link will be added
            if(m_node_linkable)
            draw_circle_flat(n->Position(),vMatrix,QVector3D(0,1,0),0.7f);
        }
        for(int i = 0;i <n->countConnected();i++){
            if(n->getConnectedIndex(i)<m_nodes.count()){
                QVector3D aux_calc_one, aux_calc_two, aux_angle;
                QMatrix4x4 aux_rotate, aux_45;
                aux_angle = n->Position() - m_nodes.value(n->getConnectedIndex(i))->Position();
                aux_angle.setY(0);

                // get the angle from the arccos function
                if(aux_angle.z()>0)
                aux_rotate.rotate(45-180*acos(aux_angle.x()/aux_angle.length())/(3.141592),0,1,0);
                else
                  aux_rotate.rotate(45+180*acos(aux_angle.x()/aux_angle.length())/(3.141592),0,1,0);

                aux_45.rotate(90,0,1,0);
                aux_calc_one = aux_rotate*(QVector3D(0,0,1));
                aux_calc_two = aux_45*aux_rotate*(QVector3D(0,0,1));

                DrawGL::DrawLine(n->Position(), m_nodes.value(n->getConnectedIndex(i))->Position(), vMatrix, QMatrix4x4(), QMatrix4x4(), QVector3D(0,1,0), m_program, pMatrix);
                DrawGL::DrawLine((n->Position()+
                         m_nodes.value(n->getConnectedIndex(i))->Position())/2.0,
                         aux_calc_one+(n->Position()+
                                   m_nodes.value(n->getConnectedIndex(i))->Position())/2.0, vMatrix, QMatrix4x4(), QMatrix4x4(), QVector3D(0,1,0), m_program, pMatrix);
                DrawGL::DrawLine((n->Position()+
                         m_nodes.value(n->getConnectedIndex(i))->Position())/2.0,
                         aux_calc_two+(n->Position()+
                                   m_nodes.value(n->getConnectedIndex(i))->Position())/2.0, vMatrix, QMatrix4x4(), QMatrix4x4(), QVector3D(0,1,0), m_program, pMatrix);
            }
        }
    }

    // draw lines last
    foreach(VisualObject *object, m_models){
        if((m_tree_removable)&&(object->getType().compare("Tree",Qt::CaseInsensitive)==0)&&(object->getTranslation().distanceToPoint(Pos)<4.0)){
            // draw a circle here
            draw_circle_flat(object->getTranslation(),vMatrix,QVector3D(1,0,0),4.0f);
        }
        if(m_wall_placable){
            if(object->getLMidHorisontal().distanceToPoint(Pos)<0.25f)
                draw_circle_flat(object->getLMidHorisontal(), vMatrix, QVector3D(0,1,0), 0.25f);
            if(object->getUMidHorisontal().distanceToPoint(Pos)<0.25f)
                draw_circle_flat(object->getUMidHorisontal(), vMatrix, QVector3D(0,1,0), 0.25f);
        }
    }
    // draw line if right clicked
    if(m_mousedown_right)
    DrawGL::DrawLine(*m_clicked_position, *m_current_position, vMatrix, QMatrix4x4(), QMatrix4x4(), QVector3D(0,1,0), m_program, pMatrix);

    // draw left clicked line(s)
    if((m_node_linkable)&&(m_mousedown_left)&&(m_node_index_selected>-1)&&(m_node_index_selected<m_nodes.count())){
        QVector3D aux_calc_one, aux_calc_two, aux_angle;
        QMatrix4x4 aux_rotate, aux_45;
        aux_angle = m_nodes.value(m_node_index_selected)->Position() - *m_current_position;
        aux_angle.setY(0);

        // get the angle from the arccos function
        if(aux_angle.z()>0)
        aux_rotate.rotate(45-180*acos(aux_angle.x()/aux_angle.length())/(3.141592),0,1,0);
        else
          aux_rotate.rotate(45+180*acos(aux_angle.x()/aux_angle.length())/(3.141592),0,1,0);

        aux_45.rotate(90,0,1,0);
        aux_calc_one = aux_rotate*(QVector3D(0,0,1));
        aux_calc_two = aux_45*aux_rotate*(QVector3D(0,0,1));

        DrawGL::DrawLine(m_nodes.value(m_node_index_selected)->Position(), *m_current_position, vMatrix, QMatrix4x4(), QMatrix4x4(), QVector3D(1,1,0), m_program, pMatrix);
        DrawGL::DrawLine((m_nodes.value(m_node_index_selected)->Position()+
                 *m_current_position)/2.0,
                 aux_calc_one+(m_nodes.value(m_node_index_selected)->Position()+
                           *m_current_position)/2.0, vMatrix, QMatrix4x4(), QMatrix4x4(), QVector3D(1,1,0), m_program, pMatrix);
        DrawGL::DrawLine((m_nodes.value(m_node_index_selected)->Position()+
                 *m_current_position)/2.0,
                 aux_calc_two+(m_nodes.value(m_node_index_selected)->Position()+
                           *m_current_position)/2.0, vMatrix, QMatrix4x4(), QMatrix4x4(), QVector3D(1,1,0), m_program, pMatrix);
    }

    // release the program for this frame
    m_program->release();
    // disable the cullmode for the frame
    glDisable(GL_CULL_FACE);
    // disable the depthtest for the frame
    glDisable(GL_DEPTH_TEST);
    // finish up the opengl frame
    glFinish();
}

void RenderState::draw_circle_flat(QVector3D center, QMatrix4x4 wvp,QVector3D color, float radius){
    const int slices = 36;
    for(int k = 0; k < slices;k++){
        DrawGL::DrawLine(radius*QVector3D(cos(2*3.14*k/slices),0,sin(2*3.14*k/slices))+center,radius*QVector3D(cos(2*3.14*(k+1)/slices),0,sin(2*3.14*(k+1)/slices))+center, wvp, QMatrix4x4(), QMatrix4x4(), color, m_program, pMatrix);
    }
}

RenderState::~RenderState(){
    delete m_program;
    delete m_position;
    delete m_clicked_position;
    delete m_node;
    delete m_plane;
    delete m_wall;
    delete m_door;
    delete m_tree;
    delete m_current_position;
}
