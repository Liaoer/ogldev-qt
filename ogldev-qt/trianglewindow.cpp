#include "trianglewindow.h"
#include "base/camera.h"
#include "texture/texture.h"
#include <QMouseEvent>

#define WINDOW_WIDTH  1366
#define WINDOW_HEIGHT 768

Camera* pGameCamera = NULL;
Texture* pTexture = NULL;

//构造函数，只是给一些成员变量一些初始值，毛用都没有
TriangleWindow::TriangleWindow()
    : m_program(0)
    , m_frame(0)
    , m_vbo(0)
    , c_vbo(0)
{
    setTitle("qt_ogldev");
    pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);
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
    //VBO是用来给顶点存放数据的.
    glBindBuffer (GL_ARRAY_BUFFER,m_vbo);


    //下面的数组是一个顶点的坐标，三位一组，表示一个三角形的顶点.
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.7f,
        0.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 0.7f,
        0.0f, 1.0f, 0.0f
     };
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f
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
    //启用VAO中对应的顶点属性数组
    glEnableVertexAttribArray(m_colAttr);
    //给对应的顶点属性数组指定数据
    glVertexAttribPointer(m_colAttr,3, GL_FLOAT, GL_FALSE, 0, 0);

    CreateIndexBuffer();
}

void TriangleWindow::CreateIndexBuffer()
{
    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               0, 1, 2 };

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
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
}
//! [4]


//该函数是渲染部分，每帧都会调用
void TriangleWindow::render()
{
    pGameCamera->OnRender();
    const qreal retinaScale = devicePixelRatio();
    //视口大小，可以理解为整个GL绘制区域占总窗口的多大，一般就是0,0,到 窗口宽高了
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    //gl的清除函数，因为每帧绘制的内容都不一样，所以要把上一帧的数据给清除了.
    glClear(GL_COLOR_BUFFER_BIT);

    //可以有好几份的shader，所以我们必须要指明我们用的是哪份shader
    m_program->bind();

    //传一个矩阵给shader，这里我们让矩阵根据时间变化进行了rotate，
    //可以看到一个旋转的三角形
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);


    CameraPos = QVector3D(1.0f, 1.0f, -3.0f);
    CameraTarget = QVector3D(0.45f, 0.0f, 1.0f);
    CameraUp = QVector3D(0.0f, 1.0f, 0.0f);

    pTexture = new Texture("./res/texture/dummy.png");

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    matrix.scale(1.0);
    //matrix.lookAt(CameraPos,CameraTarget,CameraUp);
    matrix.lookAt(pGameCamera->GetPos(), pGameCamera->GetTarget(), pGameCamera->GetUp());
    //matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);

    //glBindVertexArray(m_vao);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //顺序的draw调用
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    //渲染完毕，关闭顶点属性数组
    //glDisableVertexAttribArray(m_posAttr);
    //glDisableVertexAttribArray(m_colAttr);

    m_program->release();

    ++m_frame;
}

void TriangleWindow::mouseMoveEvent(QMouseEvent * e)
{
    printf("%d\n1",e->x());
    printf("%d\n2",e->y());
    pGameCamera->OnMouse(e->x(),e->y());
}

void TriangleWindow::mousePressEvent(QMouseEvent *e)
{
}

void TriangleWindow::mouseReleaseEvent(QMouseEvent *e)
{

}

void TriangleWindow::timerEvent(QTimerEvent *)
{

}

void TriangleWindow::keyPressEvent(QKeyEvent *event)
{
    pGameCamera->OnKeyboard(event->key());
}

void TriangleWindow::keyReleaseEvent(QKeyEvent *event)
{

}
