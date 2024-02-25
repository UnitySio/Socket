#pragma once
#include "Vector.h"

struct Transform
{
    Transform(Vector position = Vector::Zero(), Vector scale = Vector::One(), float angle = 0.f);

    bool operator==(const Transform& kTransform) const;
    bool operator!=(const Transform& kTransform) const;
    
    ~Transform() = default;

    Vector position;
    Vector scale;
    
    float angle;
};
