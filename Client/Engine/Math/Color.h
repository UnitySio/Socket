#pragma once
#include "MathTypes.h"

namespace Math
{
    struct Color
    {
        MathTypes::uint8 r;
        MathTypes::uint8 g;
        MathTypes::uint8 b;
        MathTypes::uint8 a;

        static Color Red;
        static Color Green;
        static Color Blue;
        static Color White;
        static Color Black;
        static Color Yellow;
        static Color Cyan;
        static Color Magenta;
    };
}
