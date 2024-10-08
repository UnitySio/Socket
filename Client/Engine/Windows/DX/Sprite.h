﻿#pragma once
#include "Texture.h"
#include "Math/Vector2.h"

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

    virtual bool Load(const std::wstring& kPath) override;
    
    void Split(MathTypes::uint32 cols, MathTypes::uint32 rows, Math::Vector2 pivot);

    inline void SetPPU(MathTypes::uint32 ppu) { ppu_ = ppu; }
    
    inline const std::vector<SpriteFrame>& GetFrames() const { return frames_; }
    inline MathTypes::uint32 GetPPU() const { return ppu_; }

    static const Math::Vector2 kCenter;
    static const Math::Vector2 kTopLeft;
    static const Math::Vector2 kTop;
    static const Math::Vector2 kTopRight;
    static const Math::Vector2 kLeft;
    static const Math::Vector2 kRight;
    static const Math::Vector2 kBottomLeft;
    static const Math::Vector2 kBottom;
    static const Math::Vector2 kBottomRight;

private:
    std::vector<SpriteFrame> frames_;

    MathTypes::uint32 ppu_;
    
};
