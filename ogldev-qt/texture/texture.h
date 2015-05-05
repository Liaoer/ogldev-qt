#ifndef TEXTURE_H
#define TEXTURE_H
#include <QOpenGLFunctions>
#include <QOpenGLTexture>

class Texture: protected QOpenGLFunctions
{
public:
    Texture(const char* textureFileName);
    ~Texture();
    int getTextureID();
    void setTextureID(unsigned int new_id);
    int height() const;
    void setHeight(int height);

    int width() const;
    void setWidth(int width);
private:
    QOpenGLTexture *m_qtexture;
    int m_height;
    int m_width;
    unsigned int texture_id;
    void initTexture();
};

#endif // TEXTURE_H
