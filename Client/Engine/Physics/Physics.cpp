#include "Physics.h"

#include "HitResult.h"
#include "RayCastCallback.h"
#include "Level/Level.h"
#include "Level/World.h"

bool Physics::RayCastSingle(HitResult& hit_result, const Vector& start, const Vector& end)
{
    Level* level = World::Get()->GetLevel();
    if (!level) return false;

    RayCastCallback callback;
    level->GetWorld()->RayCast(&callback, {start.x, start.y}, {end.x, end.y});

    hit_result.Distance = Vector::Distance(start, callback.GetLocation());
    hit_result.Location = callback.GetLocation();
    hit_result.Normal = callback.GetNormal();
    hit_result.TraceStart = start;
    hit_result.TraceEnd = end;
    hit_result.Actor = callback.GetActor();
    
    return callback.IsHit();
}
