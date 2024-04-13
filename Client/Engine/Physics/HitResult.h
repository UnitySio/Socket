#pragma once
#include "Math/Vector.h"

struct HitResult
{
    float distance;
    
    Vector location;
    Vector normal;
    Vector trace_start;
    Vector trace_end;
    
    class Actor* actor;
};
