#-------------------------------------------------
#
# Project created by QtCreator 2015-07-06T19:21:29
#
#-------------------------------------------------

QT += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Virtual_Creator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    renderstate.cpp \
    Objects/ModelMesh.cpp \
    Objects/Node.cpp \
    Objects/visualobject.cpp \
    Functions/mathematics.cpp \
    virtualconcierge.cpp \
    virtualconciergerenderstate.cpp \
    Functions/premises_exporter.cpp

HEADERS  += mainwindow.h \
    renderstate.h \
    Objects/ModelMesh.h \
    Objects/Node.h \
    Objects/visualobject.h \
    Functions/mathematics.h \
    virtualconcierge.h \
    virtualconciergerenderstate.h \
    Functions/premises_exporter.h

FORMS    += mainwindow.ui \
    virtualconcierge.ui

RESOURCES += \
    content.qrc
