#pragma once
#include "Texture.h"

struct SpriteFrame
{
    Math::Vector2 uv_offset;
    Math::Vector2 uv_scale;
    Math::Vector2 pivot;
};

class Sprite : public Texture
{
public:
    Sprite();
    virtual ~Sprite() override = default;

    virtual bool Load(const std::wstring& kFileName) override;
    
    void Split(MathTypes::uint32 cols, MathTypes::uint32 rows, Math::Vector2 pivot);

    inline const std::vector<SpriteFrame>& GetFrames() const { return frames_; }
    inline MathTypes::uint32 GetPPU() const { return ppu_; }

private:
    std::vector<SpriteFrame> frames_;

    MathTypes::uint32 ppu_;
    
};
