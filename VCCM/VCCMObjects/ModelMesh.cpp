/** *********************************************************************** **/
/** *********************************************************************** **/
/**     Created by:     Ruan (Baggins) Luies 23511354                       **/
/**     email:          23511354@nwu.ac.za                                  **/
/**     Project name:   Virtual Concierge Creator And Management System     **/
/**     File Name:      ModelMesh.cpp                                       **/
/**     From Date:      2015/02/24                                          **/
/**     To Date:        2015/10/01                                          **/
/** **********************************************************************  **/
/** *********************************************************************** **/
#include <QFile>
#include <QTextStream>
#include <QOpenGLFunctions>
#include <QVector2D>
#include <QVector3D>
#include <QString>
#include "VCCMObjects/ModelMesh.h"

bool ModelMesh::LoadOBJ(QString file)
 {
    vertices.clear();
    textureCoordinates.clear();
    normals.clear();
    vertexIndices.clear();
    QVector< QVector3D > temp_vertices;
    QVector< QVector2D > temp_uvs;
    QVector< QVector3D > temp_normals;
    QFile textfile(file);
    textfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream ascread(&textfile);

    if(textfile.isOpen())
    {
        QString line = ascread.readLine();

        while(!line.isNull())
        {
            QStringList list = line.split(" ");
            if(list[0]=="v")
            {
                float vertex[list.count()];
                for(int i = 0;i<list.count()-1;i++)
                     QTextStream(&list[i+1])>>vertex[i];
                temp_vertices.push_back(QVector3D(vertex[0],vertex[1],vertex[2]));
            }else
                if(list[0]=="vt")
                {
                    float uv[list.count()];
                    for(int i = 0;i<list.count()-1;i++)
                         QTextStream(&list[i+1])>>uv[i];

                    temp_uvs.push_back(QVector2D(uv[0],uv[1]));
                }else
                    if(list[0]=="vn")
                    {
                        float vertexnormal[list.count()];
                        for(int i = 0;i<list.count()-1;i++)
                             QTextStream(&list[i+1])>>vertexnormal[i];
                        temp_normals.push_back(QVector3D(vertexnormal[0],vertexnormal[1],vertexnormal[2]));
                    }else
                        if(list[0] == "f")
                        {
                            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                            for(int i = 0;i<list.count()-1;i++)
                            {
                                QStringList facelist = list[i+1].split("/");
                                QTextStream(&facelist[0])>>vertexIndex[i];
                                QTextStream(&facelist[1])>>uvIndex[i];
                                QTextStream(&facelist[2])>>normalIndex[i];
                            }
                            for(int j = 0;j<3;j++)
                            {
                            vertexIndices.push_back(vertexIndex[j]);
                            uvIndices.push_back(uvIndex[j]);
                            normalIndices.push_back(normalIndex[j]);
                            }
                        }
            line = ascread.readLine();
        }
         textfile.close();
    }
    // For each vertex of each triangle
    for( int i=0; i<vertexIndices.size(); i++ ){
        int vertexIndex = vertexIndices[i];
        QVector3D vertex = temp_vertices[ vertexIndex-1 ];
        vertices.push_back(vertex);
    }
    /*for( int i=0; i<temp_vertices.size(); i++ ){
        vertices.push_back(temp_vertices[i]);
    }*/
    // For each vertex of each triangle
    for( int i=0; i<uvIndices.size(); i++ ){
        int uvIndex = uvIndices[i];
        QVector2D uvs = temp_uvs[ uvIndex-1 ];
        textureCoordinates.push_back(uvs);
    }
    // For each vertex of each triangle
    for( int k=0; k<normalIndices.size(); k++ ){
        int normalIndex = normalIndices[k]-1;
         QVector3D normal = temp_normals[normalIndex];
         normals.push_back(normal);
    }
    return true;
 }

ModelMesh::~ModelMesh()
{
   textureCoordinates.detach();
   vertices.detach();
   normals.detach();
   vertexIndices.detach();
   uvIndices.detach();
   normalIndices.detach();
}

ModelMesh::ModelMesh(QString file)
{
   LoadOBJ(file);
}

void ModelMesh::Draw()
{
    // Draw the vertices as triangles, not linked triangles, each triangle is seperated from the other
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    //glDrawElements(GL_TRIANGLES,vertexIndices.size()*3,GL_INT,vertexIndices.constData());
}
