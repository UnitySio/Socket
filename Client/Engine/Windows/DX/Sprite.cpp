#include "Sprite.h"

bool Sprite::Load(const std::wstring& kFileName)
{
    if (!Texture::Load(kFileName)) return false;

    return true;
}
