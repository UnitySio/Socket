#pragma once
#include "Vector.h"

struct Transform
{
    Transform(Vector position = Vector::Zero(), Vector scale = Vector::One(), float angle = 0.f);
    ~Transform() = default;

    Vector position;
    Vector scale;
    
    float angle;
};
