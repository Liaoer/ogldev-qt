#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    MainWidget();
    ~MainWidget();
};

#endif // MAINWIDGET_H
