#include "texture.h"


Texture::Texture(QString textureFileName)
{
    texture = new QOpenGLTexture(QImage(":/res/texture/"+textureFileName).mirrored());
    initTexture();
}

Texture::~Texture()
{

}



void Texture::initTexture()
{
    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);

}

