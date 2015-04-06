#include "camera.h"

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

Camera::Camera(const QVector3D& Pos, const QVector3D& Target, const QVector3D& Up)
{
    m_pos    = Pos;
    m_target = Target;
    m_target.normalize();
    m_up     = Up;
    m_up.normalize();
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
