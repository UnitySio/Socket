#pragma once
#include <map>

#include "Texture.h"
#include "Math/Vector.h"

struct SpriteFrame
{
    Math::Vector offset;
    Math::Vector scale;
    Math::Vector pivot;
};

class Sprite : public Texture
{
public:
    Sprite();
    virtual ~Sprite() override = default;

    virtual bool Load(ID3D11Device* device, const std::wstring& kPath) override;

    inline const std::map<std::wstring, SpriteFrame>& GetFrames() const { return sprites_; }
    inline const SpriteFrame& GetFrame(const std::wstring& kName) const { return sprites_.at(kName); }

private:
    friend class SpriteBatch;

    bool LoadMetaData(const std::wstring& kPath);
    
    UINT ppu_;
    
    std::map<std::wstring, SpriteFrame> sprites_;
    
};
