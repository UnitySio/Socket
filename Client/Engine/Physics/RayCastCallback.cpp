#include "RayCastCallback.h"

#include "HitResult.h"
#include "box2d/b2_fixture.h"

RayCastCallback::RayCastCallback() :
    is_hit_(false),
    hit_result_()
{
}

float RayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
{
    Actor* actor = reinterpret_cast<Actor*>(fixture->GetBody()->GetUserData().pointer);
    if (!actor) return -1.f;

    is_hit_ = true;

    hit_result_.Location = { point.x, point.y };
    hit_result_.Normal = { normal.x, normal.y };
    hit_result_.Actor = actor;

    return 0.f;
}
