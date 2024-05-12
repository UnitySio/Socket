#include "Sprite.h"

Sprite::Sprite() :
    sprites_()
{
}

bool Sprite::Load(const std::wstring& kFileName)
{
    return Texture::Load(kFileName);
}

void Sprite::Split(MathTypes::uint32 rows, MathTypes::uint32 cols, Math::Vector2 pivot)
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
            
            sprites_[L"Temp_" + std::to_wstring(i * cols + j)] = frame;
        }
    }
}
