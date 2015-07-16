#ifndef VIRTUALCONCIERGE_H
#define VIRTUALCONCIERGE_H

#include <QWidget>
#include "RenderStates/virtualconciergerenderstate.h"

namespace Ui {
class VirtualConcierge;
}

class VirtualConcierge : public QWidget
{
    Q_OBJECT

public:
    explicit VirtualConcierge(QWidget *parent = 0);
    ~VirtualConcierge();

private:
    Ui::VirtualConcierge *ui;
};

#endif // VIRTUALCONCIERGE_H
