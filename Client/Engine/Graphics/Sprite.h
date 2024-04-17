#pragma once
#include <map>

#include "Texture.h"
#include "Math/MathTypes.h"
#include "Math/Vector2.h"

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

    virtual bool Load(ID3D11Device* device, const std::wstring& kPath) override;

    void Split(MathTypes::uint32 rows, MathTypes::uint32 cols, Math::Vector2 pivot);

    inline const std::map<std::wstring, SpriteFrame>& GetFrames() const { return sprites_; }
    inline const SpriteFrame& GetFrame(const std::wstring& kName) const { return sprites_.at(kName); }

private:
    friend class SpriteBatch;
    
    UINT ppu_;

    std::wstring file_name_;
    
    std::map<std::wstring, SpriteFrame> sprites_;
    
};
