#include "Color.h"

Color::Color() :
    color(0)
{
}

Color::Color(BYTE r, BYTE g, BYTE b) :
    Color(r, g, b, 255)
{
}

Color::Color(BYTE r, BYTE g, BYTE b, BYTE a)
{
    rgba[0] = r;
    rgba[1] = g;
    rgba[2] = b;
    rgba[3] = a;
}

Color::Color(const Color& kColor) :
    color(kColor.color)
{
}

Color& Color::operator=(const Color& kColor)
{
    color = kColor.color;
    return *this;
}

bool Color::operator==(const Color& kColor) const
{
    return color == kColor.color;
}

bool Color::operator!=(const Color& kColor) const
{
    return color != kColor.color;
}
