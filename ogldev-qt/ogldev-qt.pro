#-------------------------------------------------
#
# Project created by QtCreator 2015-03-16T23:47:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ogldev-qt
TEMPLATE = app


SOURCES += main.cpp \
    openglwindow/openglwindow.cpp \
    utility.cpp \
    base/mainwidget.cpp

HEADERS  += \
    openglwindow/openglwindow.h \
    base/math_3d.h \
    utility.h \
    base/mainwidget.h

RESOURCES += \
    shader.qrc

DISTFILES +=
