#-------------------------------------------------
#
# Project created by QtCreator 2014-01-29T23:37:00
#
#-------------------------------------------------

QT += core opengl
QT += qml quick
QT += sql
TARGET = VCCM
TEMPLATE = app

SOURCES += main.cpp \
    VCCMStates/RenderState.cpp \
    VCCMObjects/ModelMesh.cpp \
    VCCMUI/BackBone.cpp \
    VCCMObjects/Node.cpp \
    VCCMObjects/NodeHandler.cpp

HEADERS  += \
    VCCMStates/RenderState.h \
    VCCMObjects/ModelMesh.h \
    VCCMUI/BackBone.h \
    VCCMObjects/Node.h \
    VCCMObjects/NodeHandler.h

RESOURCES += \
    Content.qrc

OTHER_FILES += \
    VCCMContent/mainFrag.frag \
    VCCMContent/mainVert.vert \
    VCCMQML/addbutton.js

DISTFILES += \
    VCCMContent/Premises.pvc
