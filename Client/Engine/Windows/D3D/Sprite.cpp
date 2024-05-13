#include "Sprite.h"

Sprite::Sprite()
{
}

bool Sprite::Load(const std::wstring& kFileName)
{
    return Texture::Load(kFileName);
}
