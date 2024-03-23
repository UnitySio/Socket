#include "Sprite.h"

Sprite::Sprite(const std::wstring& kName, UINT ppu, Vector pivot) :
    ppu_(ppu)
{
    name_ = kName;
    
    SpriteFrame frame;
    frame.offset = {0.f, 0.f};
    frame.scale = {1.f, 1.f};
    frame.pivot = pivot;
    
    sprites_[name_] = frame;
}

bool Sprite::Load(ID3D11Device* device, const std::wstring& kPath)
{
    if (!Texture::Load(device, kPath)) return false;
    return true;
}

void Sprite::Split(UINT rows, UINT cols, Vector pivot)
{
    const float frame_width = width_ / cols;
    const float frame_height = height_ / rows;

    sprites_.clear();

    for (UINT i = 0; i < rows; ++i)
    {
        for (UINT j = 0; j < cols; ++j)
        {
            SpriteFrame frame;
            frame.offset = {static_cast<float>(j), static_cast<float>(i)};
            frame.scale = {frame_width / width_, frame_height / height_};
            frame.pivot = pivot;
            
            sprites_[name_ + L"_" + std::to_wstring(i * cols + j)] = frame;
        }
    }
}
