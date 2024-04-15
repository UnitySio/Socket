#pragma once
#include "Math/Vector.h"

struct HitResult
{
    float distance;
    
    Math::Vector location;
    Math::Vector normal;
    Math::Vector trace_start;
    Math::Vector trace_end;
    
    class Actor* actor;
};
