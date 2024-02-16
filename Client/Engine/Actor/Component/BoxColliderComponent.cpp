#include "BoxColliderComponent.h"

#include "../Actor.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner, const std::wstring& kName) :
    ColliderComponent(owner, kName)
{
    b2PolygonShape box;
    box.SetAsBox(16.f, 16.f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;
    fixture_def.density = 1.f;
    fixture_def.friction = 0.3f;

    fixture_ = owner->body_->CreateFixture(&fixture_def);
}
