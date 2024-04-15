#include "Physics.h"

#include "HitResult.h"
#include "RayCastCallback.h"
#include "box2d/b2_fixture.h"
#include "Level/Level.h"
#include "Level/World.h"

bool Physics::RayCastSingle(HitResult& hit_result, const Math::Vector2& start, const Math::Vector2& end, MathTypes::uint16 layer)
{
    RayCastCallback callback(true, layer);
    if (!PerformRayCast(callback, start, end)) return false;

    const std::vector<RayCastResult>& results = callback.GetResults();
    if (results.empty()) return false;

    Math::Vector2 location = {results[0].point.x, results[0].point.y};
    hit_result.distance = Math::Vector2::Distance(start, location);
    hit_result.location = location;
    hit_result.normal = {results[0].normal.x, results[0].normal.y};
    hit_result.trace_start = start;
    hit_result.trace_end = end;
    hit_result.actor = reinterpret_cast<Actor*>(results[0].fixture->GetBody()->GetUserData().pointer);
    
    return true;
}

bool Physics::RayCastMulti(std::vector<HitResult>& hit_results, const Math::Vector2& start, const Math::Vector2& end, MathTypes::uint16 layer)
{
    RayCastCallback callback(false, layer);
    if (!PerformRayCast(callback, start, end)) return false;

    const std::vector<RayCastResult>& results = callback.GetResults();
    if (results.empty()) return false;

    for (const auto& result : results)
    {
        HitResult hit_result;
        Math::Vector2 location = {result.point.x, result.point.y};
        hit_result.distance = Math::Vector2::Distance(start, location);
        hit_result.location = location;
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
    Level* level = World::Get()->GetLevel();
    if (!level) return false;
    
    level->GetPhysicsWorld()->RayCast(&callback, {start.x, start.y}, {end.x, end.y});
    return true;
}
