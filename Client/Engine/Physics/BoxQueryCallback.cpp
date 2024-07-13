#include "BoxQueryCallback.h"

#include "Actor/Actor.h"
#include "box2d/b2_fixture.h"

BoxQueryCallback::BoxQueryCallback(bool is_single_, MathTypes::uint16 layer) :
    is_single_(is_single_),
    layer_(layer),
    actors_()
{
}

bool BoxQueryCallback::ReportFixture(b2Fixture* fixture)
{
    b2Body* body = fixture->GetBody();
    
    Actor* actor = reinterpret_cast<Actor*>(body->GetUserData().pointer);
    if (!actor || (actor->GetLayer() & layer_) == 0) return true;

    actors_.push_back(actor);
    return !is_single_;
}
