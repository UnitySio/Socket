#include "BoxComponent.h"

#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

#include "../Actor.h"

BoxComponent::BoxComponent(Actor* actor, const std::wstring& name) : ShapeComponent(actor, name)
{
    b2PolygonShape box;
    box.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;

    fixture_ = owner_->GetBody()->CreateFixture(&fixture_def);
}

void BoxComponent::SetBox(b2Vec2 size, b2Vec2 center)
{
    b2Vec2 half_size = b2Vec2(size.x / 2.f, size.y / 2.f);
    
    b2PolygonShape box;
    box.SetAsBox(half_size.x, half_size.y, center, 0.f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;
    fixture_def.density = fixture_->GetDensity();
    fixture_def.friction = fixture_->GetFriction();

    owner_->GetBody()->DestroyFixture(fixture_);
    fixture_ = owner_->GetBody()->CreateFixture(&fixture_def);
}
