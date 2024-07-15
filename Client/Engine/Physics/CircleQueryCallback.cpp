#include "pch.h"
#include "CircleQueryCallback.h"

#include "Actor/Actor.h"
#include "box2d/b2_fixture.h"

CircleQueryCallback::CircleQueryCallback(bool is_single_, const b2Vec2& center, float radius, MathTypes::uint16 layer) :
    is_single_(is_single_),
    center_(center),
    radius_(radius),
    layer_(layer)
{
}

bool CircleQueryCallback::ReportFixture(b2Fixture* fixture)
{
    b2Body* body = fixture->GetBody();
    
    Actor* actor = reinterpret_cast<Actor*>(body->GetUserData().pointer);
    if (!actor || (actor->GetLayer() & layer_) == 0) return true;

    // 원형 범위 내 인지 체크 후 actors_에 추가
    // actors_.push_back(actor);
    
    return !is_single_;
}
