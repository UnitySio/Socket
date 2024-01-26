#include "HitResult.h"

#include "box2d/b2_fixture.h"

HitResult::HitResult() : actors_()
{
}

float HitResult::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
{
    b2Body* body = fixture->GetBody();
    if (body)
    {
        for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
        {
            Actor* actor = reinterpret_cast<Actor*>(f->GetUserData().pointer);
            if (actor)
            {
                actors_.push_back(actor);
            }
        }
        
        return fraction;
    }
    
    return 1;
}
