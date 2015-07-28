#ifndef PREMISESEXPORTER_H
#define PREMISESEXPORTER_H
#include "Objects/visualobject.h"
#include "Objects/Node.h"

class PremisesExporter
{
public:
    PremisesExporter();
    static void export_environment(QVector<VisualObject *>,QString);
    static void export_nodes(QVector<Node *>,QString);
    static void export_texture(QVector<QString>,QString);
    static void export_directories(QVector<QString>,QVector<QString>,QVector<QString>,QString);
    static bool fileExists(QString);
};

#endif // PREMISESEXPORTER_H
