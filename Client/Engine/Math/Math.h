﻿#pragma once

namespace Math
{
    float Sign(float a);
    float Lerp(float a, float b, float t);
    float Min(float a, float b);
    float Max(float a, float b);
    float Clamp(float value, float min, float max);
    float Abs(float a);
    float Pow(float f, float p);
    float Rad2Deg();
    float Deg2Rad();

    bool IsValid(float f);
}
