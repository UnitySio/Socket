#pragma once
#include <map>

#include "Texture.h"
#include "Vector.h"

struct SpriteFrame
{
    Vector offset;
    Vector scale;
    Vector pivot;
};

class Sprite : public Texture
{
public:
    Sprite(const std::wstring& kName, UINT ppu = 100, Vector pivot = {0.f, 0.f});
    virtual ~Sprite() override = default;

    virtual bool Load(ID3D11Device* device, const std::wstring& kPath) override;

    void Split(UINT rows, UINT cols, Vector pivot = {0.f, 0.f});

    inline const std::wstring& GetName() const { return name_; }
    inline const std::map<std::wstring, SpriteFrame>& GetFrames() const { return sprites_; }
    inline const SpriteFrame& GetFrame(const std::wstring& kName) const { return sprites_.at(kName); }

private:
    friend class SpriteBatch;
    
    std::wstring name_;
    
    UINT ppu_;
    
    std::map<std::wstring, SpriteFrame> sprites_;
    
};
