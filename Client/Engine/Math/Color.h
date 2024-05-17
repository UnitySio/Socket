#pragma once
#include "MathTypes.h"

namespace Math
{
    class Color
    {
    public:
        Color();
        ~Color() = default;

        inline MathTypes::uint8 GetR() const { return r; }
        inline MathTypes::uint8 GetG() const { return g; }
        inline MathTypes::uint8 GetB() const { return b; }
        inline MathTypes::uint8 GetA() const { return a; }
        
        inline MathTypes::uint32 GetColor() const { return color; }

    private:
        union
        {
            struct
            {
                MathTypes::uint8 r : 8;
                MathTypes::uint8 g : 8;
                MathTypes::uint8 b : 8;
                MathTypes::uint8 a : 8;
            };

            MathTypes::uint32 color;
        };
    };
}
