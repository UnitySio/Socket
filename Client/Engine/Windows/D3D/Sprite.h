#pragma once
#include <map>

#include "Texture.h"

struct SpriteFrame
{
    Math::Vector2 offset;
    Math::Vector2 scale;
    Math::Vector2 pivot;
};

class Sprite : public Texture
{
public:
    Sprite();
    virtual ~Sprite() override = default;

    virtual bool Load(const std::wstring& kFileName) override;

private:
    std::map<std::wstring, SpriteFrame> sprite_frames_;
    
};
