#include "Sprite.h"

Sprite::Sprite() :
    frames_(),
    ppu_(32)
{
}

bool Sprite::Load(const std::wstring& kFileName)
{
    if (!Texture::Load(kFileName)) return false;
    
    return true;;
}

void Sprite::Split(MathTypes::uint32 cols, MathTypes::uint32 rows, Math::Vector2 pivot)
{
    const float frame_width = static_cast<float>(width_) / cols;
    const float frame_height = static_cast<float>(height_) / rows;

    frames_.clear();

    for (MathTypes::uint32 y = 0; y < rows; y++)
    {
        for (MathTypes::uint32 x = 0; x < cols; x++)
        {
            SpriteFrame frame;
            frame.uv_offset.x = x;
            frame.uv_offset.y = y;
            frame.uv_scale.x = frame_width / static_cast<float>(width_);
            frame.uv_scale.y = frame_height / static_cast<float>(height_);
            frame.pivot = pivot;

            frames_.push_back(frame);
        }
    }
}
