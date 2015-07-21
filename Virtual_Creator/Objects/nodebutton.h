#ifndef NODEBUTTON_H
#define NODEBUTTON_H

#include <QPushButton>
#include <QWidget>

class NodeButton : public QPushButton
{
    Q_OBJECT
public:
    NodeButton(QWidget *parent = 0);
    ~NodeButton();
    int getIndex();
    void setIndex(int);
    void mousePressEvent(QMouseEvent * e);
private:
    int m_index;
signals:
    void clicked_index(int);
};

#endif // NODEBUTTON_H
