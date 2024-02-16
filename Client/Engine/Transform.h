#pragma once
#include "Vector.h"

struct Transform
{
    Transform();
    ~Transform() = default;

    Vector position;
    Vector scale;
    
    float angle;
};
