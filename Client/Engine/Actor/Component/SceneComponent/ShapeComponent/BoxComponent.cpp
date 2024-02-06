#include "BoxComponent.h"

#include "../../../Actor.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

BoxComponent::BoxComponent(Actor* owner, const std::wstring& kName) :
    ShapeComponent(owner, kName)
{
}

void BoxComponent::SetRelativeLocation(const b2Vec2& location)
{
    ShapeComponent::SetRelativeLocation(location);
    if (GetOwner()->GetRootComponent() == this) return;

    if (!fixture_) return;
    UpdateTransform();
}

void BoxComponent::SetRelativeRotation(float angle)
{
    ShapeComponent::SetRelativeRotation(angle);
    if (GetOwner()->GetRootComponent() == this) return;

    if (!fixture_) return;
    UpdateTransform();
}

void BoxComponent::SetBoxExtent(const b2Vec2& kExtent)
{
    SceneComponent* root = GetOwner()->GetRootComponent();
    assert(root);
    
    const float half_width = kExtent.x * 0.5f;
    const float half_height = kExtent.y * 0.5f;

    extent_ = kExtent;

    b2PolygonShape box;
    box.SetAsBox(half_width, half_height);

    CreateFixture(&box);
}

void BoxComponent::UpdateTransform()
{
    assert(GetAttachParent());

    const float half_width = extent_.x * 0.5f;
    const float half_height = extent_.y * 0.5f;

    b2Vec2 location = b2Vec2_zero;
    b2Rot rotation = b2Rot(0.f);

    if (parent_ != GetOwner()->GetRootComponent())
    {
        const b2Vec2& parent_location = parent_->GetRelativeLocation();
        
        location = parent_location + b2Mul(parent_->GetRelativeTransform().q, GetRelativeLocation());
        rotation = b2Mul(parent_->GetRelativeTransform().q, relative_transform_.q);
    }
    else
    {
        location = GetRelativeLocation();
        rotation = relative_transform_.q;
    }

    b2PolygonShape box;
    box.SetAsBox(half_width, half_height, location, rotation.GetAngle());

    CreateFixture(&box);

    for (SceneComponent* child : children_)
    {
        BoxComponent* box = dynamic_cast<BoxComponent*>(child);
        if (box)
        {
            box->UpdateTransform();
        }
    }
}

void BoxComponent::CreateFixture(b2PolygonShape* shape)
{
    b2Body* body = GetOwner()->GetRootComponent()->GetBody();
    
    b2FixtureDef fixture_def;
    fixture_def.shape = shape;
    fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

    if (fixture_)
    {
        fixture_def.density = fixture_->GetDensity();
        fixture_def.friction = fixture_->GetFriction();
        body->DestroyFixture(fixture_);
    }

    fixture_ = body->CreateFixture(&fixture_def);
}
