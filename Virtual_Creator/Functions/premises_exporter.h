/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_FUNCTIONS_PREMISES_EXPORTER_H_
#define VIRTUAL_CREATOR_FUNCTIONS_PREMISES_EXPORTER_H_

#include "Objects/visualobject.h"
#include "Objects/Node.h"

class PremisesExporter {
 public:
    PremisesExporter();
    static void export_environment(QVector<VisualObject *> object_list,
                                   QString filename);
    static void export_nodes(QVector<Node *> node_list,
                             QString filename);
    static void export_texture(QVector<QString> texture_paths,
                               QString filename);
    static void export_directories(QVector<QString> directory,
                                   QVector<QString> directory_list,
                                   QVector<QString> startup_menu,
                                   QString filename);
    static bool fileExists(QString filename);
    static void create_director();
};

#endif  // VIRTUAL_CREATOR_FUNCTIONS_PREMISES_EXPORTER_H_
