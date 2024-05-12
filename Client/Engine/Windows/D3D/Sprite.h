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

    void Split(MathTypes::uint32 rows, MathTypes::uint32 cols, Math::Vector2 pivot);

    inline const SpriteFrame& GetSprite(const std::wstring& kName) const { return sprites_.at(kName); }

private:
    std::map<std::wstring, SpriteFrame> sprites_;
    
};
