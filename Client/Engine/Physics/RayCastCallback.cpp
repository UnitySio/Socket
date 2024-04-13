#include "RayCastCallback.h"

#include "Actor/Actor.h"
#include "box2d/b2_fixture.h"

RayCastCallback::RayCastCallback(bool is_single) :
    is_single_(is_single),
    results_()
{
}

float RayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
{
    Actor* actor = reinterpret_cast<Actor*>(fixture->GetBody()->GetUserData().pointer);
    if (!actor) return -1.f;
    
    RayCastResult result;
    result.fixture = fixture;
    result.point = point;
    result.normal = normal;
    result.fraction = fraction;

    results_.push_back(result);
    return is_single_ ? 0.f : 1.f;
}
