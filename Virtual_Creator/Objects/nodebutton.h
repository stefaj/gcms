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
    void setDirectory(bool);
    bool isDirectory();
    void mousePressEvent(QMouseEvent *);
private:
    int index;
    bool directory;
signals:
    void clicked_index(int,bool);
};

#endif // NODEBUTTON_H
