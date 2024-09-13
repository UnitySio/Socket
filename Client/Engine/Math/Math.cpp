#include "pch.h"
#include "Math.h"

float Math::Sign(float a)
{
    if (a < 0.f) return -1.f;
    return 1.f;
}

float Math::Lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

float Math::Min(float a, float b)
{
    return a < b ? a : b;
}

float Math::Max(float a, float b)
{
    return a > b ? a : b;
}

float Math::Clamp(float value, float min, float max)
{
    return Math::Max(min, Math::Min(value, max));
}

float Math::Abs(float a)
{
    return a < 0.f ? -a : a;
}

float Math::Pow(float f, float p)
{
    float result = 1.f;

    for (int i = 0; i < p; ++i)
    {
        result *= f;
    }
    
    return result;
}
