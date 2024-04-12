#include "RayCastAllCallback.h"

#include "HitResult.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_math.h"

RayCastAllCallback::RayCastAllCallback() :
    hit_results_()
{
}

float RayCastAllCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
{
    Actor* actor = reinterpret_cast<Actor*>(fixture->GetBody()->GetUserData().pointer);
    if (!actor) return -1.f;

    HitResult hit_result;
    hit_result.Location = {point.x, point.y};
    hit_result.Normal = {normal.x, normal.y};
    hit_result.Actor = actor;
    
    hit_results_.push_back(hit_result);
    
    return 1.f;
}
