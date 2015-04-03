#-------------------------------------------------
#
# Project created by QtCreator 2015-03-16T23:47:15
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = ogldev-qt
TEMPLATE = app

DEFINES += "M_PI=3.14159265358979323846"
DEFINES += "M_PI_2=1.57079632679489661923"

SOURCES += main.cpp \
    openglwindow/openglwindow.cpp \
    utility.cpp \
    base/camera.cpp \
    base/mainwidget.cpp \
    trianglewindow.cpp

HEADERS  += \
    openglwindow/openglwindow.h \
    base/math_3d.h \
    utility.h \
    base/camera.h \
    base/mainwidget.h \
    trianglewindow.h

RESOURCES += \
    shader.qrc

DISTFILES +=

QT += opengl

INCLUDEPATH += \
    /Users/Shared/include/boost/
