#include "QueryCallback.h"

#include "box2d/b2_fixture.h"

QueryCallback::QueryCallback(const b2Vec2& kPoint) :
    point_(kPoint),
    fixture_(nullptr)
{
}

bool QueryCallback::ReportFixture(b2Fixture* fixture)
{
    b2Body* body = fixture->GetBody();
    if (body->GetType() == b2_dynamicBody)
    {
        const bool inside = fixture->TestPoint(point_);
        if (inside)
        {
            fixture_ = fixture;
            return false;
        }
    }
}
