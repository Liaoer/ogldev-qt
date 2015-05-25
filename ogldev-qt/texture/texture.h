#ifndef TEXTURE_H
#define TEXTURE_H
#include <QOpenGLFunctions>
#include <QOpenGLTexture>

class Texture: protected QOpenGLFunctions
{
public:
    Texture(QString textureFileName);
    int getTextureID();
    void setTextureID(unsigned int newID);
    
    ~Texture();
    QOpenGLTexture *m_qtexture;
private:

    void initTexture();
    unsigned int m_textureID;
};

#endif // TEXTURE_H
