#-------------------------------------------------
#
# Project created by QtCreator 2019-02-17T13:24:12
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Z0_Mod_Triangulation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glscene.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    glscene.h \
    qcustomplot.h

FORMS    += mainwindow.ui

LIBS    += -lopengl32
LIBS    += -lglut
LIBS    += -glut
CONFIG += opengl

