#pragma once
#include "box2d/b2_math.h"

struct RayCastResult
{
    class b2Fixture* fixture;
    b2Vec2 point;
    b2Vec2 normal;
    float fraction;
};
