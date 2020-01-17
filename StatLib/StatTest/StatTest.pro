QT += core
QT -= gui

CONFIG += c++11

TARGET = StatTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    gtest-1.7.0/src/gtest.cc \
    gtest-1.7.0/src/gtest-all.cc \
    gtest-1.7.0/src/gtest-death-test.cc \
    gtest-1.7.0/src/gtest-filepath.cc \
    gtest-1.7.0/src/gtest-port.cc \
    gtest-1.7.0/src/gtest-printers.cc \
    gtest-1.7.0/src/gtest-test-part.cc \
    gtest-1.7.0/src/gtest-typed-test.cc

INCLUDEPATH+= "../"
INCLUDEPATH +="gtest-1.7.0/include"
INCLUDEPATH +="gtest-1.7.0/"



LIBS+= "../../build-StatLib-Desktop_Qt_5_7_0_MinGW_32bit-Release/release/libStatLib.a"


HEADERS += \
    ../statlib.h
