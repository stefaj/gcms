/* Copyright 2015 Ruan Luies */
#ifndef VIRTUAL_CREATOR_OBJECTS_NODEBUTTON_H_
#define VIRTUAL_CREATOR_OBJECTS_NODEBUTTON_H_

#include <QPushButton>
#include <QWidget>

class NodeButton : public QPushButton {
    Q_OBJECT

 public:
    explicit NodeButton(QWidget *parent = 0);
    ~NodeButton();
    int getIndex();
    void setIndex(int index);
    void setDirectory(bool is_directory);
    bool isDirectory();
    void mousePressEvent(QMouseEvent *event);
 private:
    int index;
    bool directory;
 signals:
    void clicked_index(int, bool);
};

#endif  // VIRTUAL_CREATOR_OBJECTS_NODEBUTTON_H_
