#include "Sprite.h"

Sprite::Sprite(const std::wstring& kName)
{
    name_ = kName;
}

bool Sprite::Load(ID3D11Device* device, const std::wstring& path)
{
    if (!Texture::Load(device, path)) return false;

    SpriteFrame frame = {0, 0, 1, 1};
    sprites_[name_ + L"_0"] = frame;

    return true;
}
