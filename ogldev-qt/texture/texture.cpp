#include "texture.h"


Texture::Texture(QString textureFileName)
{
    m_qtexture = new QOpenGLTexture(QImage(":/res/texture/"+textureFileName).mirrored());
    initTexture();
}

Texture::~Texture()
{

}

int Texture::getTextureID()
{
    return this->m_textureID;
}

void Texture::setTextureID(unsigned int newID)
{
    this->m_textureID = newID;
}



void Texture::initTexture()
{
    // Set nearest filtering mode for texture minification
    m_qtexture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    m_qtexture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    m_qtexture->setWrapMode(QOpenGLTexture::Repeat);

}

