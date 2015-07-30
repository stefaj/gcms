#include <QFile>
#include <QTextStream>
#include <QOpenGLFunctions>
#include <QVector2D>
#include <QVector3D>
#include <QString>
#include "Objects/ModelMesh.h"

bool ModelMesh::LoadOBJ(QString file){
    this->vertices.clear();
    this->textureCoordinates.clear();
    this->normals.clear();
    this->vertexIndices.clear();
    QVector< QVector3D > temp_vertices;
    QVector< QVector2D > temp_uvs;
    QVector< QVector3D > temp_normals;
    QFile textfile(file);
    textfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ascread(&textfile);

    if(textfile.isOpen()){
        QString line = ascread.readLine();
        while(!line.isNull()){
            QStringList list = line.split(" ");
            if(list[0]=="v"){
                float vertex[list.count()];
                for(int i = 0;i<list.count()-1;i++)
                     QTextStream(&list[i+1])>>vertex[i];
                temp_vertices.push_back(QVector3D(vertex[0],vertex[1],vertex[2]));
            }else
                if(list[0]=="vt"){
                    float uv[list.count()];
                    for(int i = 0;i<list.count()-1;i++)
                         QTextStream(&list[i+1])>>uv[i];

                    temp_uvs.push_back(QVector2D(uv[0],uv[1]));
                }else
                    if(list[0]=="vn"){
                        float vertexnormal[list.count()];
                        for(int i = 0;i<list.count()-1;i++)
                             QTextStream(&list[i+1])>>vertexnormal[i];
                        temp_normals.push_back(QVector3D(vertexnormal[0],vertexnormal[1],vertexnormal[2]));
                    }else
                        if(list[0] == "f"){
                            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                            for(int i = 0;i<list.count()-1;i++){
                                QStringList facelist = list[i+1].split("/");
                                QTextStream(&facelist[0])>>vertexIndex[i];
                                QTextStream(&facelist[1])>>uvIndex[i];
                                QTextStream(&facelist[2])>>normalIndex[i];
                            }
                            for(int j = 0;j<3;j++){
                            this->vertexIndices.push_back(vertexIndex[j]);
                            this->uvIndices.push_back(uvIndex[j]);
                            this->normalIndices.push_back(normalIndex[j]);
                            }
                        }
            line = ascread.readLine();
        }
         textfile.close();
    }
    // For each vertex of each triangle
    for( int i=0; i<this->vertexIndices.size(); i++ ){
        int vertexIndex = this->vertexIndices[i];
        QVector3D vertex = temp_vertices[ vertexIndex-1 ];
        this->vertices.push_back(vertex);
    }
    // For each vertex of each triangle
    for( int i=0; i<this->uvIndices.size(); i++ ){
        int uvIndex = this->uvIndices[i];
        QVector2D uvs = temp_uvs[ uvIndex-1 ];
        this->textureCoordinates.push_back(uvs);
    }
    // For each vertex of each triangle
    for( int k=0; k<this->normalIndices.size(); k++ ){
        int normalIndex = this->normalIndices[k]-1;
         QVector3D normal = temp_normals[normalIndex];
         this->normals.push_back(normal);
    }
    return true;
 }

ModelMesh::~ModelMesh(){
   this->textureCoordinates.detach();
   this->vertices.detach();
   this->normals.detach();
   this->vertexIndices.detach();
   this->uvIndices.detach();
   this->normalIndices.detach();
}

ModelMesh::ModelMesh(QString file){LoadOBJ(file);}

void ModelMesh::Draw(){
    // Draw the vertices as triangles, not linked triangles, each triangle is seperated from the other
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
    //glDrawElements(GL_TRIANGLES,vertexIndices.size()*3,GL_INT,vertexIndices.constData());
}
