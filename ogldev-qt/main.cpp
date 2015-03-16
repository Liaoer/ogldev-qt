
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
    void render() Q_DECL_OVERRIDE;
    void initVBO();
private:

    int m_frame;
    GLuint m_vbo;
};

//构造函数，只是给一些成员变量一些初始值，毛用都没有
TriangleWindow::TriangleWindow()
    :m_frame(0)
    ,m_vbo(0)
{
}

//初始化VBO，VBO可以看作是显卡上一块显存空间的指针，我们通过它把一些不经常变动的数据，
//上传到显卡上，这样好处是减少对显卡传输的数据的负载，减少显卡占用带宽.
void TriangleWindow::initVBO()
{
    //先创建一个vbo对象，创建成功后,m_vbo的值就会被修改成一个对象索引，诸如1,2,3,4之类
    glGenBuffers (1,&m_vbo);
    //切记Opengl是状态机，我们要先绑定这个VBO,参数GL_ARRAY_BUFFER的意思就是告诉我们，
    //这个鸡巴VBO是用来给顶点存放数据的.
    glBindBuffer (GL_ARRAY_BUFFER,m_vbo);
    //下面的数组是一个顶点的坐标，三位一组，表示一个三角形的顶点.
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    //把如上表示的数据，上传到m_vbo在显卡占用的内存中.
    glBufferData (GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

}


//该函数是渲染部分，每帧都会调用
void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    //视口大小，可以理解为整个GL绘制区域占总窗口的多大，一般就是鸡巴0,0,到 窗口宽高了
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    //gl的清除函数，因为每帧绘制的内容都不一样，所以要把上一帧的数据给清除了.
    glClear(GL_COLOR_BUFFER_BIT);

    //绑定我们的VBO
    glBindBuffer (GL_ARRAY_BUFFER,m_vbo);
    //注意最后一个参数是0，因为最后的这个地址，是根据在该VBO的内存空间里计算的，我们只存了顶点,
    //没几把存别的，所以以零开始，三位一组.
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
    QSurfaceFormat format;
    format.setSamples(16);
    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();
   // window.setAnimating(true);

    return app.exec();
}


