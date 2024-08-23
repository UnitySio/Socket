#pragma once
#include "box2d/types.h"
#include "Math/Color.h"
#include "Math/Math.h"

static Math::Color MakeColor(b2HexColor color, float alpha)
{
    return Math::Color
    {
        static_cast<MathTypes::uint8>((color >> 16) & 0xFF),
        static_cast<MathTypes::uint8>((color >> 8) & 0xFF),
        static_cast<MathTypes::uint8>(color & 0xFF),
        static_cast<MathTypes::uint8>(0xFF * alpha)
    };
}

class DebugDraw
{
public:
    DebugDraw();
    ~DebugDraw() = default;

    void DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color);
    
};
