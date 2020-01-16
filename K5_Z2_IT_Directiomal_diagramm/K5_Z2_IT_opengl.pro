#-------------------------------------------------
#
# Project created by QtCreator 2019-10-30T16:30:54
#
#-------------------------------------------------

QT       += core gui opengl
QT       += opengl
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = K5_Z2_IT_opengl
TEMPLATE = app

DEFINES += CHARTDIR_HIDE_OBSOLETE _CRT_SECURE_NO_WARNINGS


SOURCES += main.cpp\
        mainwindow.cpp \
    glscene.cpp \
    qchartviewer.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    glscene.h \
    qchartviewer.h \
    chartdir.h \
    bchartdir.h \
    memblock.h \
    qcustomplot.h

FORMS    += mainwindow.ui

LIBS    += -lopengl32
LIBS    += -lglut
LIBS    += -lglut32
LIBS    += -glut

LIBS += -L"D:\Qt Projects\1MAG\K5_Z2_IT_opengl" -lchartdir60

CONFIG  += opengl
