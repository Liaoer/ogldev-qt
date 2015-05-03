#include "camera.h"
#include <math.h>

const static float STEP_SCALE = 0.1f;
const static float EDGE_STEP = 0.5f;
const static int MARGIN = 10;

Camera::Camera(int WindowWidth, int WindowHeight)
{
    m_windowWidth  = WindowWidth;
    m_windowHeight = WindowHeight;
    m_pos    = QVector3D(0.0f, 0.0f, 0.0f);
    m_target = QVector3D(0.0f, 0.0f, 1.0f);
    m_target.normalize();
    m_up     = QVector3D(0.0f, 1.0f, 0.0f);

    Init();
}

Camera::~Camera()
{

}

Camera::Camera(int WindowWidth, int WindowHeight,const QVector3D& Pos, const QVector3D& Target, const QVector3D& Up)
{
    m_windowWidth  = WindowWidth;
    m_windowHeight = WindowHeight;
    m_pos    = Pos;
    m_target = Target;
    m_target.normalize();
    m_up     = Up;
    m_up.normalize();

    Init();
}

void Camera::Init()
{
   QVector3D HTarget = QVector3D(m_target.x(), 0.0, m_target.z()); // 水平target向量
   HTarget.normalize();

   if(HTarget.z()>0.0f){
       if(HTarget.x()>0.0f){
           m_AngleH = 360.0f - ToDegree(asin(HTarget.z()));
       }else{
           m_AngleH = 180.0f + ToDegree(asin(HTarget.z()));
       }
   }else
   {
       if (HTarget.x() >= 0.0f)
       {
           m_AngleH = ToDegree(asin(-HTarget.z()));
       }
       else
       {
           m_AngleH = 90.0f + ToDegree(asin(-HTarget.z()));
       }
   }

   m_AngleV = -ToDegree(asin(m_target.y()));

   m_OnUpperEdge = false;
   m_OnLowerEdge = false;
   m_OnLeftEdge  = false;
   m_OnRightEdge = false;
   m_mousePos.setX(m_windowWidth / 2);
   m_mousePos.setY(m_windowHeight / 2);

}

void Camera::Update()
{
    //const QVector3D Vaxis = QVector3D(0.0f, 1.0f, 0.0f);
    const Vector3f Vaxis(0.0f, 1.0f, 0.0f);
    // Rotate the view vector by the horizontal angle around the vertical axis
    Vector3f View(1.0f, 0.0f, 0.0f);
    View.Rotate(m_AngleH, Vaxis);
    View.Normalize();

    // Rotate the view vector by the vertical angle around the horizontal axis
    Vector3f Haxis = Vaxis.Cross(View);
    Haxis.Normalize();
    View.Rotate(m_AngleV, Haxis);

    QVector3D tmpView;
    tmpView.setX(View.x);
    tmpView.setY(View.y);
    tmpView.setZ(View.z);

    QVector3D tmpHaxis;
    tmpHaxis.setX(Haxis.x);
    tmpHaxis.setY(Haxis.y);
    tmpHaxis.setZ(Haxis.z);

    m_target = tmpView;
    m_target.normalize();

    m_up = QVector3D::crossProduct(m_target,tmpHaxis);
    m_up.normalize();
}

void Camera::OnMouse(int x, int y)
{
    const int DeltaX = x - m_mousePos.x();
    const int DeltaY = y - m_mousePos.y();

    m_mousePos.setX(x);
    m_mousePos.setY(y);

    m_AngleH += (float)DeltaX / 20.0f;
    m_AngleV += (float)DeltaY / 20.0f; // 缩放系数

    if (DeltaX == 0) {
    if (x <= MARGIN) {
    m_OnLeftEdge = true;
    }
    else if (x >= (m_windowWidth - MARGIN)) {
    m_OnRightEdge = true;
    }
    }
    else {
    m_OnLeftEdge = false;
    m_OnRightEdge = false;
    }
    if (DeltaY == 0) {
    if (y <= MARGIN) {
    m_OnUpperEdge = true;
    }
    else if (y >= (m_windowHeight - MARGIN)) {
    m_OnLowerEdge = true;
    }
    }
    else {
    m_OnUpperEdge = false;
    m_OnLowerEdge = false;
    }
    //Update();
}

bool Camera::OnKeyboard(int Key)
{
    bool Ret = false;

    switch (Key) {

    case Qt::Key_Up:
        {
            m_pos += (m_target * STEP_SCALE);
            Ret = true;
        }
        break;

    case Qt::Key_Down:
        {
            m_pos -= (m_target * STEP_SCALE);
            Ret = true;
        }
        break;

    case Qt::Key_Left:
        {
            QVector3D Left = QVector3D::crossProduct(m_target,m_up);
            Left.normalize();
            Left *= STEP_SCALE;
            m_pos += Left;
            Ret = true;
        }
        break;

    case Qt::Key_Right:
        {
            QVector3D Right = QVector3D::crossProduct(m_up,m_target);
            Right.normalize();
            Right *= STEP_SCALE;
            m_pos += Right;
            Ret = true;
        }
        break;
    }

    return Ret;
}

void Camera::OnRender()
{
    bool ShouldUpdate = false;
    if (m_OnLeftEdge) {
    m_AngleH -= 0.1f;
    ShouldUpdate = true;
    }
    else if (m_OnRightEdge) {
    m_AngleH += 0.1f;
    ShouldUpdate = true;
    }
    if (m_OnUpperEdge) {
    if (m_AngleV > -90.0f) {
        m_AngleV -= 0.1f;
        ShouldUpdate = true;
    }
    }
    else if (m_OnLowerEdge) {
        if (m_AngleV < 90.0f) {
        m_AngleV += 0.1f;
        ShouldUpdate = true;
    }
}
    if (ShouldUpdate) {
        Update();
    }
}
