#pragma once
#include <vector>

#include "Math/MathTypes.h"
#include "Math/Vector2.h"

class Actor;
class World;
struct HitResult;

class Physics
{
public:
    static bool RayCast(HitResult& hit_result, const Math::Vector2& start, const Math::Vector2& end, MathTypes::uint16 layer = 0xFFFF);
    static bool RayCastAll(std::vector<HitResult>& hit_results, const Math::Vector2& start, const Math::Vector2& end, MathTypes::uint16 layer = 0xFFFF);

    static bool OverlapBox(const Math::Vector2& center, const Math::Vector2& extent, Actor** actor, MathTypes::uint16 layer = 0xFFFF);
    static bool OverlapBoxAll(const Math::Vector2& center, const Math::Vector2& extent, std::vector<Actor*>& actors, MathTypes::uint16 layer = 0xFFFF);
    static bool OverlapCircle(const Math::Vector2& center, float radius, Actor** actor, MathTypes::uint16 layer = 0xFFFF);
    static bool OverlapCircleAll(const Math::Vector2& center, float radius, std::vector<Actor*>& actors, MathTypes::uint16 layer = 0xFFFF);
    
};
