/* Copyright 2015 Ruan Luies */

#include <QFile>
#include <QTextStream>
#include <QOpenGLFunctions>
#include <QVector2D>
#include <QVector3D>
#include <QString>
#include "Objects/ModelMesh.h"

bool ModelMesh::LoadOBJ(QString file) {
  this->vertices.clear();
  this->texture_coordinates.clear();
  this->normals.clear();
  this->vertex_indices.clear();
  QVector< QVector3D > temp_vertices;
  QVector< QVector2D > temp_uvs;
  QVector< QVector3D > temp_normals;
  QFile textfile(file);
  textfile.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream ascread(&textfile);
  if ( textfile.isOpen() ) {
    QString line = ascread.readLine();
    while ( !line.isNull() ) {
      QStringList list = line.split(" ");
      const unsigned int ListCount = list.count();
      if ( list[0] == "v" ) {
        float *vertex = (float*)malloc(sizeof(float) * ListCount);
        //float vertex[ListCount];
        for ( unsigned int i = 0; i < ListCount - 1; i++ )
            QTextStream(&list[i + 1]) >> vertex[i];
          temp_vertices.push_back(QVector3D(vertex[0],
                                            vertex[1],
                                            vertex[2]));
          free(vertex);
        } else if ( list[0] == "vt" ) {
                float *uv = (float*)malloc(sizeof(float) * ListCount);
                //float uv[ListCount];
                for ( unsigned int i = 0; i < ListCount - 1; i++ ) {
                  QTextStream(&list[i+1]) >> uv[i];
                }
                  temp_uvs.push_back(QVector2D(uv[0], uv[1]));
                free(uv);
        } else if ( list[0] == "vn" ) {
                //float vertexnormal[ListCount];
                float *vertexnormal = (float*)malloc(sizeof(float) * ListCount);
                for ( unsigned int i = 0; i < ListCount - 1; i++ ) {
                  QTextStream(&list[i+1]) >> vertexnormal[i];
                }
                  temp_normals.push_back(QVector3D(vertexnormal[0],
                                                   vertexnormal[1],
                                                   vertexnormal[2]));
                free(vertexnormal);
        } else if ( list[0] == "f" ) {
                unsigned int vertexIndex[3],
                             uvIndex[3],
                             normalIndex[3];
                for ( int i = 0; i < list.count() - 1; i++ ) {
                  QStringList facelist = list[i+1].split("/");
                  QTextStream(&facelist[0]) >> vertexIndex[i];
                  QTextStream(&facelist[1]) >> uvIndex[i];
                  QTextStream(&facelist[2]) >> normalIndex[i];
                }
                for ( int j = 0; j < 3; j++ ) {
                  this->vertex_indices.push_back(vertexIndex[j]);
                  this->uv_indices.push_back(uvIndex[j]);
                  this->normal_indices.push_back(normalIndex[j]);
                }
        }
        line = ascread.readLine();
    }
    textfile.close();
  }
    // For each vertex of each triangle
    for ( int i = 0; i < this->vertex_indices.size(); i++ ) {
      int vertexIndex = this->vertex_indices[i];
      QVector3D vertex = temp_vertices[ vertexIndex-1 ];
      this->vertices.push_back(vertex);
    }
    // For each vertex of each triangle
    for ( int i = 0; i < this->uv_indices.size(); i++ ) {
      int uvIndex = this->uv_indices[i];
      QVector2D uvs = temp_uvs[ uvIndex-1 ];
      this->texture_coordinates.push_back(uvs);
    }
    // For each vertex of each triangle
    for ( int k = 0; k < this->normal_indices.size(); k++ ) {
      int normalIndex = this->normal_indices[k] - 1;
      QVector3D normal = temp_normals[normalIndex];
      this->normals.push_back(normal);
    }
    return true;
}

ModelMesh::~ModelMesh() {
  this->texture_coordinates.detach();
  this->vertices.detach();
  this->normals.detach();
  this->vertex_indices.detach();
  this->uv_indices.detach();
  this->normal_indices.detach();
}

ModelMesh::ModelMesh(QString file) {LoadOBJ(file);}

void ModelMesh::Draw() {
  // Draw the vertices as triangles, not linked triangles,
  // each triangle is seperated from the other
  glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
}
