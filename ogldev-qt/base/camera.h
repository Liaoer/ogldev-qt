#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QVector2D>
#include "utility.h"

class Camera
{
public:
    Camera();
    ~Camera();
    Camera(int WindowWidth, int WindowHeight,const QVector3D& Pos, const QVector3D& Target, const QVector3D& Up);

    bool OnKeyboard(int Key);
    void OnMouse(int x, int y);
    void OnRender();

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
    void Init();
    void Update();

    QVector3D m_pos;
    QVector3D m_target;
    QVector3D m_up;

    int m_windowWidth;
    int m_windowHeight;

    float m_AngleH;
    float m_AngleV;

    bool m_OnUpperEdge;
    bool m_OnLowerEdge;
    bool m_OnLeftEdge;
    bool m_OnRightEdge;

    QVector2D m_mousePos;
};

#endif // CAMERA_H
