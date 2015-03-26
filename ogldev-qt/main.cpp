/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "openglwindow/openglwindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QtCore/qmath.h>



//继承一个QT的OPENGL窗口类，我们用透过它来绘制图像以及使用Opengl的相关函数，如果你需要在别的类里使用opengl的功能，
//需要继承QOpenGLFunctions类.
class TriangleWindow : public OpenGLWindow
{
public:
    TriangleWindow();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;
    void initVBO();
private:
    void loadShader();

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
    GLuint m_vbo;
    GLuint m_vao;
    GLuint c_vbo;
};

//构造函数，只是给一些成员变量一些初始值，毛用都没有
TriangleWindow::TriangleWindow()
    : m_program(0)
    , m_frame(0)
    , m_vbo(0)
    , m_vao(0)
    , c_vbo(0)
{
    setTitle("qt_ogldev");
}


//初始化VBO，VBO可以看作是显卡上一块显存空间的指针，我们通过它把一些不经常变动的数据，
//上传到显卡上，这样好处是减少对显卡传输的数据的负载，减少显卡占用带宽.
void TriangleWindow::initVBO()
{
    //glGenVertexArrays(1,&m_vao);
    //glBindVertexArray(m_vao);

    //先创建一个vbo对象，创建成功后,m_vbo的值就会被修改成一个对象索引，诸如1,2,3,4之类
    glGenBuffers (1,&m_vbo);
    //切记Opengl是状态机，我们要先绑定这个VBO,参数GL_ARRAY_BUFFER的意思就是告诉我们，
    //这个鸡巴VBO是用来给顶点存放数据的.
    glBindBuffer (GL_ARRAY_BUFFER,m_vbo);


    //下面的数组是一个顶点的坐标，三位一组，表示一个三角形的顶点.
    GLfloat vertices[] = {
        -0.7f, -0.7f,0,
        0.0f, 0.7f,0,
        0.7f, -0.7f,0
     };
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    //把如上表示的数据，上传到m_vbo在显卡占用的内存中.
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    //注意最后一个参数是0，因为最后的这个地址，是根据在该VBO的内存空间里计算的，我们只存了顶点,
    //没几把存别的，所以以零开始，三位一组.
    glEnableVertexAttribArray(m_posAttr);
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1,&c_vbo);
    glBindBuffer (GL_ARRAY_BUFFER,c_vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);
    glEnableVertexAttribArray(m_colAttr);
    glVertexAttribPointer(m_colAttr,3, GL_FLOAT, GL_FALSE, 0, 0);

}

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    //app.setApplicationName(" qt_ogldev");
    //app.setApplicationVersion("0.1");
    QSurfaceFormat format;
    format.setSamples(16);

    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();
    window.setAnimating(true);

    return app.exec();
}



//载入shader，这里没有直接使用Opengl的函数，而是使用了Qt对GL的辅助库来装载Shader，当然
//用原版的GL函数也是可以的.
void TriangleWindow::loadShader()
{
    m_program = new QOpenGLShaderProgram(this); // 创建个着色器对象
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vs"); // 编译及绑定
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fs");
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr"); // 绑定和获取一个顶点属性的位置
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
}

void TriangleWindow::initialize()
{
    loadShader();
    initVBO();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
//! [4]

//该函数是渲染部分，每帧都会调用
void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    //视口大小，可以理解为整个GL绘制区域占总窗口的多大，一般就是鸡巴0,0,到 窗口宽高了
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    //gl的清除函数，因为每帧绘制的内容都不一样，所以要把上一帧的数据给清除了.
    glClear(GL_COLOR_BUFFER_BIT);

    //因为鸡巴可以有好几份的shader，所以我们必须要指明我们用的是哪份shader
    m_program->bind();

    //传一个矩阵给shader，这里我们让矩阵根据时间变化进行了rotate，
    //可以看到一个旋转的三角形

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    //matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);

    //glBindVertexArray(m_vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    //渲染完毕，关闭顶点属性数组
    //glDisableVertexAttribArray(m_posAttr);
    //glDisableVertexAttribArray(m_colAttr);

    m_program->release();

    ++m_frame;
}


//! [5]
