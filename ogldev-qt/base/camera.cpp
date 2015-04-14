#include "camera.h"
#include <math.h>

const static float StepScale = 0.1f;

Camera::Camera()
{
    m_pos    = QVector3D(0.0f, 0.0f, 0.0f);
    m_target = QVector3D(0.0f, 0.0f, 1.0f);
    m_up     = QVector3D(0.0f, 1.0f, 0.0f);
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

}

bool Camera::OnKeyboard(int Key)
{
    bool Ret = false;

    switch (Key) {

    case Qt::Key_Up:
        {
            m_pos += (m_target * StepScale);
            Ret = true;
        }
        break;

    case Qt::Key_Down:
        {
            m_pos -= (m_target * StepScale);
            Ret = true;
        }
        break;

    case Qt::Key_Left:
        {
            QVector3D Left = QVector3D::crossProduct(m_target,m_up);
            Left.normalize();
            Left *= StepScale;
            m_pos += Left;
            Ret = true;
        }
        break;

    case Qt::Key_Right:
        {
            QVector3D Right = QVector3D::crossProduct(m_up,m_target);
            Right.normalize();
            Right *= StepScale;
            m_pos += Right;
            Ret = true;
        }
        break;
    }

    return Ret;
}
