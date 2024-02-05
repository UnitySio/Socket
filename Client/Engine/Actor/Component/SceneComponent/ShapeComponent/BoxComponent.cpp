#include "BoxComponent.h"

#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

BoxComponent::BoxComponent(Actor* owner, const std::wstring& kName) :
    ShapeComponent(owner, kName),
    fixture_(nullptr)
{
}

void BoxComponent::SetRelativeLocation(const b2Vec2& location)
{
    ShapeComponent::SetRelativeLocation(location);
    
    const float half_width = extent_.x * 0.5f;
    const float half_height = extent_.y * 0.5f;

    b2PolygonShape box;
    box.SetAsBox(half_width, half_height, GetRelativeLocation(), GetRelativeRotation());

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;
    
    if (fixture_)
    {
        fixture_def.density = fixture_->GetDensity();
        fixture_def.friction = fixture_->GetFriction();
        body_->DestroyFixture(fixture_);
    }

    fixture_ = body_->CreateFixture(&fixture_def);
}

void BoxComponent::SetRelativeRotation(float angle)
{
    ShapeComponent::SetRelativeRotation(angle);
    
    const float half_width = extent_.x * 0.5f;
    const float half_height = extent_.y * 0.5f;

    b2PolygonShape box;
    box.SetAsBox(half_width, half_height, GetRelativeLocation(), GetRelativeRotation());

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;
    
    if (fixture_)
    {
        fixture_def.density = fixture_->GetDensity();
        fixture_def.friction = fixture_->GetFriction();
        body_->DestroyFixture(fixture_);
    }

    fixture_ = body_->CreateFixture(&fixture_def);
}

void BoxComponent::SetBoxExtent(const b2Vec2& kExtent)
{
    const float half_width = kExtent.x * 0.5f;
    const float half_height = kExtent.y * 0.5f;

    extent_ = kExtent;

    b2PolygonShape box;
    box.SetAsBox(half_width, half_height);

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;

    if (fixture_)
    {
        fixture_def.density = fixture_->GetDensity();
        fixture_def.friction = fixture_->GetFriction();
        body_->DestroyFixture(fixture_);
    }

    fixture_ = body_->CreateFixture(&fixture_def);
}
