#-------------------------------------------------
#
# Project created by QtCreator 2019-11-27T18:52:23
#
#-------------------------------------------------

QT       += core gui opengl
QT       += opengl
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = K5_Mod_Z2_Diffuzia
TEMPLATE = app

DEFINES += CHARTDIR_HIDE_OBSOLETE _CRT_SECURE_NO_WARNINGS


SOURCES += main.cpp\
        mainwindow.cpp \
    glscene.cpp \
    qcustomplot.cpp \
    qchartviewer.cpp

HEADERS  += mainwindow.h \
    glscene.h \
    qcustomplot.h \
    bchartdir.h \
    chartdir.h \
    qchartviewer.h \
    memblock.h

FORMS    += mainwindow.ui


LIBS    += -lopengl32
LIBS    += -lglu32

LIBS += -L"D:\Qt Projects\1MAG\K5_Mod_Z2_Diffuzia3\K5_Mod_Z2_Diffuzia" -lchartdir60

CONFIG  += opengl

DISTFILES +=
