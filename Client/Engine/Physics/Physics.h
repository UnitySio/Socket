#pragma once
#include <vector>

#include "Math/Vector.h"

struct HitResult;
enum ActorLayer : unsigned short;

class Physics
{
public:
    static bool RayCastSingle(HitResult& hit_result, const Vector& start, const Vector& end);
    static bool RayCastMulti(std::vector<HitResult>& hit_results, const Vector& start, const Vector& end);
    
};
