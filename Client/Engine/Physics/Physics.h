#pragma once
#include <vector>

#include "Math/Vector.h"

struct HitResult;

class Physics
{
public:
    static bool RayCastSingle(HitResult& hit_result, const Math::Vector& start, const Math::Vector& end);
    static bool RayCastMulti(std::vector<HitResult>& hit_results, const Math::Vector& start, const Math::Vector& end);

private:
    static bool PerformRayCast(class RayCastCallback& callback, const Math::Vector& start, const Math::Vector& end);
    
};
