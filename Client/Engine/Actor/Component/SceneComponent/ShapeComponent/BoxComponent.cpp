#include "BoxComponent.h"

#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

BoxComponent::BoxComponent(Actor* owner, const std::wstring& kName) :
    ShapeComponent(owner, kName),
    fixture_(nullptr)
{
    b2PolygonShape box;
    box.SetAsBox(1.f, 1.f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;

    fixture_ = body_->CreateFixture(&fixture_def);
}

void BoxComponent::SetBoxExtent(const b2Vec2& kExtent)
{
    const float half_width = kExtent.x * 0.5f;
    const float half_height = kExtent.y * 0.5f;

    b2PolygonShape box;
    box.SetAsBox(half_width, half_height);

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;
    fixture_def.density = fixture_->GetDensity();
    fixture_def.friction = fixture_->GetFriction();

    body_->DestroyFixture(fixture_);
    fixture_ = body_->CreateFixture(&fixture_def);
}
