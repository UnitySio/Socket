#include "TransformComponent.h"

#include "Actor/Actor.h"
#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

TransformComponent::TransformComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    body_(nullptr),
    scale_(Vector::One())
{
    b2BodyDef body_def;
    body_def.userData.pointer = reinterpret_cast<uintptr_t>(owner);

    b2World* world = owner->GetWorld();
    body_ = world->CreateBody(&body_def);
}

void TransformComponent::SetLocation(Vector location)
{
    assert(body_);
    body_->SetTransform({location.x, location.y}, body_->GetAngle());
}

void TransformComponent::SetRotation(float angle)
{
    assert(body_);

    const float radian = angle * b2_pi / 180.f;
    body_->SetTransform(body_->GetPosition(), radian);
}

Vector TransformComponent::GetLocation() const
{
    assert(body_);
    
    b2Vec2 position = body_->GetPosition();
    return {position.x, position.y};
}

Vector TransformComponent::GetRightVector() const
{
    assert(body_);
    
    b2Vec2 x = body_->GetTransform().q.GetXAxis();
    return {x.x, x.y};
}

Vector TransformComponent::GetUpVector() const
{
    assert(body_);
    
    b2Vec2 y = body_->GetTransform().q.GetYAxis();
    return {y.x, y.y};
}

float TransformComponent::GetRotation() const
{
    assert(body_);

    const float radian = body_->GetAngle();
    const float angle = radian * 180.f / b2_pi;
    return angle;
}
