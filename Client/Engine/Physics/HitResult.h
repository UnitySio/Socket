#pragma once
#include "Math/Vector2.h"

struct HitResult
{
    float distance;
    
    Math::Vector2 location;
    Math::Vector2 normal;
    Math::Vector2 trace_start;
    Math::Vector2 trace_end;
    
    class Actor* actor;
};
