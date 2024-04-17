#include "Sprite.h"

#include "ProjectSettings.h"

Sprite::Sprite() :
    ppu_(32)
{
}

bool Sprite::Load(ID3D11Device* device, const std::wstring& kPath)
{
    const std::wstring kFinalPath = ProjectSettings::kPath.at(L"GameData") + kPath;
    if (!Texture::Load(device, kFinalPath)) return false;
    
    const std::wstring kFileName = kPath.substr(kPath.find_last_of(L"/\\") + 1, kPath.find_last_of(L".") - kPath.find_last_of(L"/\\") - 1);
    file_name_ = kFileName;
    
    return true;
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
            
            sprites_[file_name_ + L"_" + std::to_wstring(i * cols + j)] = frame;
        }
    }
}
