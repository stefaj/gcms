#include "premises_exporter.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>
PremisesExporter::PremisesExporter(){

}

void PremisesExporter::export_environment(QVector<VisualObject *> objects,QString name){
    if(QDir().mkdir("VirtualConcierge"))
        qDebug()<<"Success in Creating Directory 'VirtualConcierge'";

    if(!QDir().cd("VirtualConcierge"))
        qDebug()<<"Directory 'VirtualConcierge' does not exists";

    QFile file("VirtualConcierge/"+name);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);

        // write the nodes
        for(int l = 0;l < objects.count();l++){
            out <<"o,"<< l <<","
                <<objects.value(l)->getType()<<","
                <<objects.value(l)->getTranslation().x()<<","
                <<objects.value(l)->getTranslation().y()<<","
                <<objects.value(l)->getTranslation().z()<<","
                <<objects.value(l)->getRotation().x()<<","
                <<objects.value(l)->getRotation().y()<<","
                <<objects.value(l)->getRotation().z()<<","
                <<objects.value(l)->getScaling().x()<<","
                <<objects.value(l)->getScaling().y()<<","
                <<objects.value(l)->getScaling().z()<<","
                <<objects.value(l)->getTextureID()<<"\n";
        }

        // optional, as QFile destructor will already do it:
        file.close();
}

void PremisesExporter::export_texture(QVector<QString> textures,QString name)
{
    if(QDir().mkdir("VirtualConcierge"))
        qDebug()<<"Success in Creating Directory 'VirtualConcierge'";

    if(!QDir().cd("VirtualConcierge"))
        qDebug()<<"Directory 'VirtualConcierge' does not exists";

    QFile file("VirtualConcierge/"+name);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);

        // write the nodes
        for(int l = 0;l < textures.count();l++){
            out <<"t,"<< l <<","
                <<textures.value(l)<<"\n";
        }

        // optional, as QFile destructor will already do it:
        file.close();
}

void PremisesExporter::export_nodes(QVector<Node *> nodes,QString name){
if(QDir().mkdir("VirtualConcierge"))
    qDebug()<<"Success in Creating Directory 'VirtualConcierge'";

if(!QDir().cd("VirtualConcierge"))
    qDebug()<<"Directory 'VirtualConcierge' does not exists";

QFile file("VirtualConcierge/"+name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    // write the nodes
    for(int l = 0;l < nodes.count();l++){
        out <<"n,"<< l <<","
            << nodes.value(l)->Position().x()<<","
            << nodes.value(l)->Position().y()<<","
            << nodes.value(l)->Position().z()<<","
            << nodes.value(l)->getName()<<"\n";
    }
    // write the links to each node
    for(int k= 0;k < nodes.count();k++){
        for(int j = 0; j<nodes.value(k)->countConnected();j++)
        out <<"j,"<< k<<","<<nodes.value(k)->getConnectedIndex(j)<<"\n";
    }

    // optional, as QFile destructor will already do it:
    file.close();
}

bool PremisesExporter::fileExists(QString path) {
    QFileInfo checkFile(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}
