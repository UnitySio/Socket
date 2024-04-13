#pragma once
#include <vector>

#include "Math/Vector.h"

struct HitResult;

class Physics
{
public:
    static bool RayCastSingle(HitResult& hit_result, const Vector& start, const Vector& end);
    static bool RayCastMulti(std::vector<HitResult>& hit_results, const Vector& start, const Vector& end);

private:
    static bool PerformRayCast(class RayCastCallback& callback, const Vector& start, const Vector& end);
    
};
