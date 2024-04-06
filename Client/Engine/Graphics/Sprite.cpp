#include "Sprite.h"

#include "yaml-cpp/yaml.h"

Sprite::Sprite() :
    ppu_(0)
{
}

bool Sprite::Load(ID3D11Device* device, const std::wstring& kPath)
{
    if (!Texture::Load(device, kPath)) return false;
    if (!LoadMetaData(kPath)) return false;
    return true;
}

bool Sprite::LoadMetaData(const std::wstring& kPath)
{
    const std::string path(kPath.begin(), kPath.end());
    YAML::Node root = YAML::LoadFile(path + ".meta");
    if (!root.IsDefined()) return false;

    ppu_ = root["sprite_pixel_per_unit"].as<int>();

    for (const auto sprite : root["sprite_sheet"]["sprites"])
    {
        SpriteFrame frame;
        frame.offset = {
            sprite["offset"]["x"].as<float>(),
            sprite["offset"]["y"].as<float>()
        };
        frame.scale = {
            sprite["scale"]["x"].as<float>(),
            sprite["scale"]["y"].as<float>()
        };
        frame.pivot = {
            sprite["pivot"]["x"].as<float>(),
            sprite["pivot"]["y"].as<float>()
        };

        const std::string name = sprite["name"].as<std::string>();
        const std::wstring w_name(name.begin(), name.end());
        sprites_[w_name] = frame;
    }

    if (sprites_.size() == 0)
    {
        SpriteFrame frame;
        frame.offset = {0.f, 0.f};
        frame.scale = {1.f, 1.f};
        frame.pivot = {
            root["sprite_pivot"]["x"].as<float>(),
            root["sprite_pivot"]["y"].as<float>()
        };

        const std::string name = root["sprite_name"].as<std::string>();
        const std::wstring w_name(name.begin(), name.end());
        sprites_[w_name] = frame;
    }

    return true;
}
