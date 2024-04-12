#include "RayCastCallback.h"

#include "box2d/b2_fixture.h"

RayCastCallback::RayCastCallback() :
    is_hit_(false),
    location_(),
    actor_(nullptr)
{
}

float RayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
{
    is_hit_ = true;
    
    location_ = {point.x, point.y};
    normal_ = {normal.x, normal.y};
    
    actor_ = reinterpret_cast<Actor*>(fixture->GetBody()->GetUserData().pointer);
    
    return fraction;
}
