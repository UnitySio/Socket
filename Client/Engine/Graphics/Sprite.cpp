#include "Sprite.h"

Sprite::Sprite(const std::wstring& kName, UINT ppu) :
    ppu_(ppu)
{
    name_ = kName;
}

bool Sprite::Load(ID3D11Device* device, const std::wstring& kPath)
{
    if (!Texture::Load(device, kPath)) return false;

    SpriteFrame frame = {0, 0, 1, 1};
    sprites_[name_ + L"_0"] = frame;

    return true;
}

void Sprite::Split(UINT rows, UINT cols)
{
    const float frame_width = width_ / cols;
    const float frame_height = height_ / rows;

    sprites_.clear();

    for (UINT i = 0; i < rows; ++i)
    {
        for (UINT j = 0; j < cols; ++j)
        {
            SpriteFrame frame;
            frame.offset_x = j;
            frame.offset_y = i;
            frame.scale_x = frame_width / width_;
            frame.scale_y = frame_height / height_;
            sprites_[name_ + L"_" + std::to_wstring(i * cols + j)] = frame;
        }
    }
}
