#-------------------------------------------------
#
# Project created by QtCreator 2015-03-07T17:47:28
#
#-------------------------------------------------

QT       += gui core
QT += network
QT += sql
TARGET = information_request_client
CONFIG   += console

TEMPLATE = app


SOURCES += main.cpp \
    informationrequest.cpp \
    server.cpp\
    tcpsocket.cpp

HEADERS += \
    informationrequest.h \
    server.h\
    tcpsocket.h
