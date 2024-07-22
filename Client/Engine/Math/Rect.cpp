#include "pch.h"
#include "Rect.h"

Math::Rect::Rect() :
    x(0.f),
    y(0.f),
    width(0.f),
    height(0.f)
{
}

Math::Rect::Rect(float x, float y, float width, float height) :
    x(x),
    y(y),
    width(width),
    height(height)
{
}
