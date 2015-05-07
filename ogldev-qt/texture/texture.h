#ifndef TEXTURE_H
#define TEXTURE_H
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLTexture>

class Texture: protected QOpenGLFunctions
{
public:
    Texture(QString textureFileName);
    ~Texture();
    QOpenGLTexture *texture;
private:
    void initTexture();
};

#endif // TEXTURE_H
