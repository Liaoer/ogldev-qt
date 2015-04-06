#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>

class Camera
{
public:
    Camera();
    ~Camera();
    Camera(const QVector3D& Pos, const QVector3D& Target, const QVector3D& Up);

    bool OnKeyboard(int Key);

    const QVector3D& GetPos() const
    {
        return m_pos;
    }

    const QVector3D& GetTarget() const
    {
        return m_target;
    }

    const QVector3D& GetUp() const
    {
        return m_up;
    }

private:

    QVector3D m_pos;
    QVector3D m_target;
    QVector3D m_up;
};

#endif // CAMERA_H
