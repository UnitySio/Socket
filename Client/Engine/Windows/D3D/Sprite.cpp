#include "Sprite.h"

Sprite::Sprite() :
    sprite_frames_()
{
}

bool Sprite::Load(const std::wstring& kFileName)
{
    return Texture::Load(kFileName);
}
