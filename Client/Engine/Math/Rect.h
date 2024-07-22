#pragma once
#include "Vector2.h"

namespace Math
{
    struct Rect
    {
        Rect();
        Rect(float x, float y, float width, float height);

        inline float Left() const { return x; }
        inline float Right() const { return x + width; }
        inline float Top() const { return y; }
        inline float Bottom() const { return y + height; }
        
        inline Math::Vector2 Center() const { return {x + width / 2.f, y + height / 2.f}; }
        
        float x;
        float y;
        float width;
        float height;
    };
}
