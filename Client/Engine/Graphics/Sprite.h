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
    Sprite(const std::wstring& kName, UINT ppu);
    virtual ~Sprite() override = default;

    virtual bool Load(ID3D11Device* device, const std::wstring& kPath) override;

    void Split(UINT rows, UINT cols);

    inline const std::wstring& GetName() const { return name_; }
    inline const std::map<std::wstring, SpriteFrame>& GetFrames() const { return sprites_; }
    inline const SpriteFrame& GetFrame(const std::wstring& kName) const { return sprites_.at(kName); }

private:
    std::wstring name_;
    
    UINT ppu_;
    
    std::map<std::wstring, SpriteFrame> sprites_;
    
};
