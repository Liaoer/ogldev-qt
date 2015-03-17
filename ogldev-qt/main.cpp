
#include "openglwindow/openglwindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>
#include "base/math_3d.h"


class TriangleWindow : public OpenGLWindow
{
public:
    TriangleWindow();
    void initialize() Q_DECL_OVERRIDE;
    void initVBO();
    void render() Q_DECL_OVERRIDE;
private:

    int m_frame;
    GLuint m_vbo;
    GLuint m_vao;
};

TriangleWindow::TriangleWindow()
    :m_frame(0)
{
}


void TriangleWindow::initVBO()
{
    //vao
    glGenVertexArrays(1,&m_vao);
    glBindVertexArray(m_vao);
    //vbo
    glGenBuffers (1,&m_vbo);
    glBindBuffer (GL_ARRAY_BUFFER,m_vbo);
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    glBufferData (GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

}


void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer (GL_ARRAY_BUFFER,m_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    ++m_frame;
}


void TriangleWindow::initialize()
{
    initVBO();
}


int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    app.setApplicationName("qt-ogldev");
    QSurfaceFormat format;
    format.setSamples(16);
    TriangleWindow window;

    window.setFormat(format);
    window.resize(640, 480);
    window.show();
    window.setAnimating(true);

    return app.exec();
}


