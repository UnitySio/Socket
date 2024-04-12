#pragma once
#include "Math/Vector.h"

struct HitResult
{
    float Distance;
    
    Vector Location;
    Vector Normal;
    Vector TraceStart;
    Vector TraceEnd;
    
    class Actor* Actor;
};
