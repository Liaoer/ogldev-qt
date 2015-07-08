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
    trianglewindow.cpp \
    base/math_3d.cpp \
    texture/texture.cpp \
    base/vertexdata.cpp \
    external/SOIL/image_DXT.c \
    external/SOIL/image_helper.c \
    external/SOIL/SOIL.c \
    external/SOIL/stb_image_aug.c

HEADERS  += \
    openglwindow/openglwindow.h \
    base/math_3d.h \
    utility.h \
    base/camera.h \
    base/mainwidget.h \
    trianglewindow.h \
    texture/texture.h \
    base/matrix3x3.h \
    base/matrix4x4.h \
    base/vector3.h \
    base/Compiler/poppack1.h \
    base/Compiler/pstdint.h \
    base/Compiler/pushpack1.h \
    base/vertexdata.h \
    external/SOIL/image_DXT.h \
    external/SOIL/image_helper.h \
    external/SOIL/SOIL.h \
    external/SOIL/stb_image_aug.h \
    external/SOIL/stbi_DDS_aug.h \
    external/SOIL/stbi_DDS_aug_c.h \

RESOURCES += \
    shader.qrc \
    textures.qrc

DISTFILES +=

QT += opengl

INCLUDEPATH += \
    /Users/Shared/include/boost/
