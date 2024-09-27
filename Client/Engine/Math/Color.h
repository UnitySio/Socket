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

        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color White;
        static const Color Black;
        static const Color Gray;
        static const Color Yellow;
        static const Color Cyan;
        static const Color Magenta;
        static const Color Pink;
    };
}
