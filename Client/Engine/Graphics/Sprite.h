#pragma once
#include <map>

#include "Texture.h"

struct SpriteFrame
{
    float offset_x;
    float offset_y;
    float scale_x;
    float scale_y;
};

class Sprite : public Texture
{
public:
    Sprite(const std::wstring& kName);
    virtual ~Sprite() override = default;

    virtual bool Load(ID3D11Device* device, const std::wstring& path) override;

    inline const std::wstring& GetName() const { return name_; }
    inline const std::map<std::wstring, SpriteFrame>& GetSprites() const { return sprites_; }

private:
    std::wstring name_;
    
    std::map<std::wstring, SpriteFrame> sprites_;
    
};
