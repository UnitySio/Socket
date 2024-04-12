#include "Physics.h"

#include "HitResult.h"
#include "RayCastAllCallback.h"
#include "RayCastCallback.h"
#include "Level/Level.h"
#include "Level/World.h"

bool Physics::RayCastSingle(HitResult& hit_result, const Vector& start, const Vector& end)
{
    Level* level = World::Get()->GetLevel();
    if (!level) return false;

    RayCastCallback callback;
    level->GetWorld()->RayCast(&callback, {start.x, start.y}, {end.x, end.y});

    hit_result = callback.GetHitResult();
    hit_result.Distance = Vector::Distance(start, hit_result.Location);
    hit_result.TraceStart = start;
    hit_result.TraceEnd = end;

    return callback.IsHit();
}

bool Physics::RayCastMulti(std::vector<HitResult>& hit_results, const Vector& start, const Vector& end)
{
    Level* level = World::Get()->GetLevel();
    if (!level) return false;

    RayCastAllCallback callback;
    level->GetWorld()->RayCast(&callback, {start.x, start.y}, {end.x, end.y});

    hit_results = callback.GetHitResults();
    for (auto& hit_result : hit_results)
    {
        hit_result.Distance = Vector::Distance(start, hit_result.Location);
        hit_result.TraceStart = start;
        hit_result.TraceEnd = end;
    }

    return !hit_results.empty();
}
