#include "Physics.h"

#include "HitResult.h"
#include "RayCastCallback.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_world.h"
#include "Level/Level.h"
#include "Level/World.h"

bool Physics::RayCastSingle(HitResult& hit_result, const Math::Vector2& start, const Math::Vector2& end, MathTypes::uint16 layer)
{
    RayCastCallback callback(true, layer);
    if (!PerformRayCast(callback, start, end)) return false;

    const std::vector<RayCastResult>& kResults = callback.GetResults();
    if (kResults.empty()) return false;

    Math::Vector2 position = {kResults[0].point.x, kResults[0].point.y};
    hit_result.distance = Math::Vector2::Distance(start, position);
    hit_result.position = position;
    hit_result.normal = {kResults[0].normal.x, kResults[0].normal.y};
    hit_result.trace_start = start;
    hit_result.trace_end = end;
    hit_result.actor = reinterpret_cast<Actor*>(kResults[0].fixture->GetBody()->GetUserData().pointer);
    
    return true;
}

bool Physics::RayCastMulti(std::vector<HitResult>& hit_results, const Math::Vector2& start, const Math::Vector2& end, MathTypes::uint16 layer)
{
    RayCastCallback callback(false, layer);
    if (!PerformRayCast(callback, start, end)) return false;

    const std::vector<RayCastResult>& kResults = callback.GetResults();
    if (kResults.empty()) return false;

    for (const auto& result : kResults)
    {
        HitResult hit_result;
        Math::Vector2 position = {result.point.x, result.point.y};
        hit_result.distance = Math::Vector2::Distance(start, position);
        hit_result.position = position;
        hit_result.normal = {result.normal.x, result.normal.y};
        hit_result.trace_start = start;
        hit_result.trace_end = end;
        hit_result.actor = reinterpret_cast<Actor*>(result.fixture->GetBody()->GetUserData().pointer);
        
        hit_results.push_back(hit_result);
    }

    return true;
}

bool Physics::PerformRayCast(RayCastCallback& callback, const Math::Vector2& start, const Math::Vector2& end)
{
    World::Get()->physics_world_->RayCast(&callback, {start.x, start.y}, {end.x, end.y});
    return true;
}
