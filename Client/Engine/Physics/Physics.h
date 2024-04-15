#pragma once
#include <vector>

#include "Math/Vector2.h"

struct HitResult;

class Physics
{
public:
    static bool RayCastSingle(HitResult& hit_result, const Math::Vector2& start, const Math::Vector2& end);
    static bool RayCastMulti(std::vector<HitResult>& hit_results, const Math::Vector2& start, const Math::Vector2& end);

private:
    static bool PerformRayCast(class RayCastCallback& callback, const Math::Vector2& start, const Math::Vector2& end);
    
};
