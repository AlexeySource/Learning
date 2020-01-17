#-------------------------------------------------
#
# Project created by QtCreator 2019-12-24T23:19:35
#
#-------------------------------------------------

QT       -= gui

TARGET = StatLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += statlib.cpp

HEADERS += statlib.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
