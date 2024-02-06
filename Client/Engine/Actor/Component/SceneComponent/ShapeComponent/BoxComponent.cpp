#include "BoxComponent.h"

#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

BoxComponent::BoxComponent(Actor* owner, const std::wstring& kName) :
    ShapeComponent(owner, kName)
{
}

void BoxComponent::SetRelativeLocation(const b2Vec2& location)
{
    ShapeComponent::SetRelativeLocation(location);

    UpdateTransform();
}

void BoxComponent::SetRelativeRotation(float angle)
{
    ShapeComponent::SetRelativeRotation(angle);

    UpdateTransform();
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
    fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

    if (fixture_)
    {
        fixture_def.density = fixture_->GetDensity();
        fixture_def.friction = fixture_->GetFriction();
        body_->DestroyFixture(fixture_);
    }

    fixture_ = body_->CreateFixture(&fixture_def);
}

void BoxComponent::UpdateTransform()
{
    if (!fixture_ || !GetAttachParent()) return;

    const float half_width = extent_.x * 0.5f;
    const float half_height = extent_.y * 0.5f;

    const b2Transform& parent_relative_transform = GetAttachParent()->GetRelativeTransform();
    const b2Vec2 final_location = parent_relative_transform.p + b2Mul(parent_relative_transform.q, GetRelativeLocation());

    b2PolygonShape box;
    box.SetAsBox(half_width, half_height, final_location, GetRelativeRotation());

    b2FixtureDef fixture_def;
    fixture_def.shape = &box;
    fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
    
    if (fixture_)
    {
        fixture_def.density = fixture_->GetDensity();
        fixture_def.friction = fixture_->GetFriction();
        body_->DestroyFixture(fixture_);
    }

    fixture_ = body_->CreateFixture(&fixture_def);
}
