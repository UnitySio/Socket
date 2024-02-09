#include "ShapeComponent.h"

#include "../../../Actor.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_world.h"

ShapeComponent::ShapeComponent(Actor* owner, const std::wstring& kName) :
    SceneComponent(owner, kName),
    fixture_(nullptr)
{
}

void ShapeComponent::SetRelativeLocation(const b2Vec2& location)
{
    SceneComponent::SetRelativeLocation(location);
    
    if (owner_->GetRootComponent() == this) return;
    assert(GetAttachParent());
    
    if (!fixture_) return;
    UpdateTransform();
}

void ShapeComponent::SetRelativeRotation(float angle)
{
    SceneComponent::SetRelativeRotation(angle);
    
    if (owner_->GetRootComponent() == this) return;
    assert(GetAttachParent());
    
    if (!fixture_) return;
    UpdateTransform();
}

void ShapeComponent::CreateFixture(b2Shape* shape)
{
    b2Body* body = owner_->body_;
    
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

void ShapeComponent::UpdateChildTransforms()
{
    for (SceneComponent* child : children_)
    {
        ShapeComponent* shape = dynamic_cast<ShapeComponent*>(child);
        if (shape) shape->UpdateTransform();
    }
}
