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
};

#endif // PREMISESEXPORTER_H