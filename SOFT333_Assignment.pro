#-------------------------------------------------
#
# Project created by QtCreator 2014-03-24T21:00:22
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SOFT333_Assignment
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    RenderArea.cpp \
    Matrix.cpp \
    Vector.cpp \
    Model.cpp

HEADERS  += MainWindow.h \
    RenderArea.h \
    Matrix.h \
    Vector.h \
    Model.h

FORMS    += MainWindow.ui
