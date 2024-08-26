#include "pch.h"
#include "DebugDraw.h"

static inline Math::Color MakeRGBA8(b2HexColor color, float alpha)
{
    return {
        static_cast<MathTypes::uint8>((color >> 16) & 0xFF),
        static_cast<MathTypes::uint8>((color >> 8) & 0xFF),
        static_cast<MathTypes::uint8>(color & 0xFF),
        static_cast<MathTypes::uint8>(0xFF * alpha)
    };
}
