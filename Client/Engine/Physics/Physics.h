#pragma once
#include "Math/Vector.h"

enum ActorLayer : unsigned short;

class Physics
{
public:
    static bool RayCastSingle(struct HitResult& hit_result, const Vector& start, const Vector& end);
    
};
