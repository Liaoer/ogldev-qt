#ifndef TRIANGLEWINDOW_H
#define TRIANGLEWINDOW_H

#include "openglwindow/openglwindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QtCore/qmath.h>

#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>

//继承一个QT的OPENGL窗口类，我们用透过它来绘制图像以及使用Opengl的相关函数，如果你需要在别的类里使用opengl的功能，
//需要继承QOpenGLFunctions类.
class TriangleWindow : public OpenGLWindow
{
public:
    TriangleWindow();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;
    void initVBO();
    void CreateIndexBuffer();
protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
private:
    void loadShader();

    QVector3D CameraPos;
    QVector3D CameraTarget;
    QVector3D CameraUp;

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
    GLuint m_vbo;
    //GLuint m_vao;
    GLuint c_vbo;
    GLuint IBO;

    QBasicTimer timer;
    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;
};

#endif // TRIANGLEWINDOW_H
