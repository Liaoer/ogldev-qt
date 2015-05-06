#ifndef TEXTUREPOOL_H
#define TEXTUREPOOL_H

#include "texture.h"
#include <map>
#include <string>

class TexturePool
{
public:
    Texture *createOrGetTexture(const char *file_name);
    static TexturePool *getInstance();
private:
    TexturePool();
    static TexturePool * instance;
    std::map<std::string, Texture*> texture_list;
};

#endif // TEXTUREPOOL_H
