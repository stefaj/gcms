#-------------------------------------------------
#
# Project created by QtCreator 2015-07-06T19:21:29
#
#-------------------------------------------------

QT += core gui
QT += opengl
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Virtual_Creator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Objects/ModelMesh.cpp \
    Objects/Node.cpp \
    Objects/visualobject.cpp \
    Functions/mathematics.cpp \
    virtualconcierge.cpp \
    Functions/premises_exporter.cpp \
    Objects/NodeHandler.cpp \
    RenderStates/renderstate.cpp \
    RenderStates/virtualconciergerenderstate.cpp \
    Functions/drawgl.cpp \
    Objects/nodebutton.cpp \
    SMTP/smtp.cpp \
    userinterfacecreator.cpp

HEADERS  += mainwindow.h \
    Objects/ModelMesh.h \
    Objects/Node.h \
    Objects/visualobject.h \
    Functions/mathematics.h \
    virtualconcierge.h \
    Functions/premises_exporter.h \
    Objects/NodeHandler.h \
    RenderStates/renderstate.h \
    RenderStates/virtualconciergerenderstate.h \
    Functions/drawgl.h \
    Objects/nodebutton.h \
    SMTP/smtp.h \
    userinterfacecreator.h \
    main.h

FORMS    += mainwindow.ui \
    virtualconcierge.ui \
    userinterfacecreator.ui

RESOURCES += \
    content.qrc

DISTFILES +=
