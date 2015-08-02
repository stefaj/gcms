/* Copyright 2015 Ruan Luies */

#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include "./premises_exporter.h"

PremisesExporter::PremisesExporter() {
}

void PremisesExporter::export_environment(QVector<VisualObject *> objects,
                                          QString name) {
    if ( QDir().mkdir("VirtualConcierge") )
        qDebug() << "Success in Creating Directory 'VirtualConcierge'";

    if ( !QDir().cd("VirtualConcierge") )
        qDebug() << "Directory 'VirtualConcierge' does not exists";

    QFile file("VirtualConcierge/"+name);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);

        // write the nodes
        for ( int l = 0; l < objects.count(); l++ ) {
            out << "o," << l << ","
                << objects.value(l)->getType() << ","
                << objects.value(l)->getTranslation().x() << ","
                << objects.value(l)->getTranslation().y() << ","
                << objects.value(l)->getTranslation().z() << ","
                << objects.value(l)->getRotation().x() << ","
                << objects.value(l)->getRotation().y() << ","
                << objects.value(l)->getRotation().z() << ","
                << objects.value(l)->getScaling().x() << ","
                << objects.value(l)->getScaling().y() << ","
                << objects.value(l)->getScaling().z() << ","
                << objects.value(l)->getTextureID() << "\n";
        }

        // optional, as QFile destructor will already do it:
        file.close();
}

void PremisesExporter::export_texture(QVector<QString> textures,
                                      QString name) {
    if ( QDir().mkdir("VirtualConcierge") )
        qDebug() << "Success in Creating Directory 'VirtualConcierge'";

    if ( !QDir().cd("VirtualConcierge") )
        qDebug() << "Directory 'VirtualConcierge' does not exists";

    QFile file("VirtualConcierge/"+name);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);

        // write the nodes
        for ( int l = 0; l < textures.count(); l++ ) {
            out << "t," << l <<","
                << textures.value(l) << "\n";
        }

        // optional, as QFile destructor will already do it:
        file.close();
}

void PremisesExporter::export_nodes(QVector<Node *> nodes,
                                    QString name) {
if ( QDir().mkdir("VirtualConcierge") )
    qDebug() << "Success in Creating Directory 'VirtualConcierge'";

if ( !QDir().cd("VirtualConcierge") )
    qDebug() << "Directory 'VirtualConcierge' does not exists";

QFile file("VirtualConcierge/" + name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    // write the nodes
    for ( int l = 0; l < nodes.count(); l++ ) {
        if ( nodes.value(l)->getSignificant() ) {
            out << "n," << l << ","
            << nodes.value(l)->Position().x() << ","
            << nodes.value(l)->Position().y() << ","
            << nodes.value(l)->Position().z() << ","
            << nodes.value(l)->getName() << ","
            << "1\n";
        } else {
            out << "n," << l << ","
            << nodes.value(l)->Position().x() << ","
            << nodes.value(l)->Position().y() << ","
            << nodes.value(l)->Position().z() << ","
            << nodes.value(l)->getName() << ","
            << "0\n";
        }
    }
    // write the links to each node
    for ( int k = 0; k < nodes.count(); k++ ) {
        for ( int j = 0; j < nodes.value(k)->countConnected(); j++ ) {
          const int linked_node = nodes.value(k)->getConnectedIndex(j);
          if ( k != linked_node ) {
          out << "j," << k << "," << linked_node << "\n";
          }
        }
    }
    // optional, as QFile destructor will already do it:
    file.close();
}

void PremisesExporter::export_directories(QVector<QString> directory,
                                          QVector<QString> directory_list,
                                          QVector<QString> startup_menu,
                                          QString filename) {
    if ( QDir().mkdir("VirtualConcierge") )
        qDebug() << "Success in Creating Directory 'VirtualConcierge'";

    if ( !QDir().cd("VirtualConcierge") )
        qDebug() << "Directory 'VirtualConcierge' does not exists";

    QFile file("VirtualConcierge/" + filename);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);

        // write the directories
        for ( int l = 0; l < directory.count(); l++ ) {
            out << "d," << directory.value(l) << "\n";
        }

        // write the directory list
        for ( int l = 0; l < directory_list.count(); l++ ) {
            out << "dl,"<< directory_list.value(l) << "\n";
        }

        // write the startup
        for ( int l = 0; l < startup_menu.count(); l++ ) {
            out << "dd," <<startup_menu.value(l) << "\n";
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
