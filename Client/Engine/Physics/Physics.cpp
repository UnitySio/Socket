#include "Physics.h"

#include "BoxQueryCallback.h"
#include "HitResult.h"
#include "RayCastCallback.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_world.h"
#include "Level/Level.h"
#include "Level/World.h"

bool Physics::RayCast(HitResult& hit_result, const Math::Vector2& start, const Math::Vector2& end, MathTypes::uint16 layer)
{
    RayCastCallback callback(true, layer);
    World::Get()->physics_world_->RayCast(&callback, {start.x, start.y}, {end.x, end.y});

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

bool Physics::RayCastAll(std::vector<HitResult>& hit_results, const Math::Vector2& start, const Math::Vector2& end, MathTypes::uint16 layer)
{
    RayCastCallback callback(false, layer);
    World::Get()->physics_world_->RayCast(&callback, {start.x, start.y}, {end.x, end.y});

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

bool Physics::OverlapBox(const Math::Vector2& center, const Math::Vector2& extent, Actor** actor, MathTypes::uint16 layer)
{
    b2AABB aabb;
    aabb.lowerBound = {center.x - extent.x, center.y - extent.y};
    aabb.upperBound = {center.x + extent.x, center.y + extent.y};

    BoxQueryCallback callback(false, layer);
    World::Get()->physics_world_->QueryAABB(&callback, aabb);

    if (callback.GetActors().empty()) return false;
    *actor = callback.GetActors()[0];

    return true;
}

bool Physics::OverlapBoxAll(const Math::Vector2& center, const Math::Vector2& extent, std::vector<Actor*>& actors, MathTypes::uint16 layer)
{
    b2AABB aabb;
    aabb.lowerBound = {center.x - extent.x, center.y - extent.y};
    aabb.upperBound = {center.x + extent.x, center.y + extent.y};

    BoxQueryCallback callback(true, layer);
    World::Get()->physics_world_->QueryAABB(&callback, aabb);

    if (callback.GetActors().empty()) return false;
    actors = callback.GetActors();

    return true;
}
