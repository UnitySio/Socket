#pragma once
#include <vector>

#include "Math/MathTypes.h"
#include "Math/Vector2.h"

struct HitResult;

class Physics
{
public:
    static bool RayCastSingle(HitResult& hit_result, const Math::Vector2& start, const Math::Vector2& end, MathTypes::uint16 layer = 0xFFFF);
    static bool RayCastMulti(std::vector<HitResult>& hit_results, const Math::Vector2& start, const Math::Vector2& end, MathTypes::uint16 layer = 0xFFFF);

private:
    static bool PerformRayCast(class RayCastCallback& callback, const Math::Vector2& start, const Math::Vector2& end);
    
};
