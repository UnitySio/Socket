#include "TransformComponent.h"

#include "Actor/Actor.h"
#include "box2d/b2_body.h"

TransformComponent::TransformComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    world_location_(Vector::Zero()),
    world_scale_(Vector::One()),
    relative_location_(Vector::Zero()),
    relative_scale_(Vector::One()),
    world_rotation_z_(0.f),
    relative_rotation_z_(0.f)
{
}

void TransformComponent::TickComponent(float delta_time)
{
    ActorComponent::TickComponent(delta_time);

    b2Body* body = GetOwner()->body_;
    if (!body || body->GetType() == b2_staticBody) return;
    if (!GetOwner()->parent_)
    {
        const b2Vec2 position = body->GetPosition();
        relative_location_ = {position.x, position.y};

        const float angle = body->GetAngle();
        relative_rotation_z_ = angle * 180.f / b2_pi;

        UpdateTransform();
    }
}

void TransformComponent::SetRelativeLocation(Vector location)
{
    // assert(body_);
    // body_->SetTransform({location.x, location.y}, body_->GetAngle());

    relative_location_ = location;
    UpdateTransform();
}

void TransformComponent::SetRelativeRotationZ(float angle)
{
    // assert(body_);
    //
    // const float radian = angle * b2_pi / 180.f;
    // body_->SetTransform(body_->GetPosition(), radian);
}

Vector TransformComponent::GetRightVector() const
{
    // assert(body_);
    //
    // b2Vec2 x = body_->GetTransform().q.GetXAxis();
    // return {x.x, x.y};

    return Vector::Zero();
}

Vector TransformComponent::GetUpVector() const
{
    // assert(body_);
    //
    // b2Vec2 y = body_->GetTransform().q.GetYAxis();
    // return {y.x, y.y};

    return Vector::Zero();
}

void TransformComponent::UpdateTransform()
{
    if (GetOwner()->parent_)
    {
        Vector parent_location = GetOwner()->parent_->transform_->world_location_;
        const float parent_rotation = GetOwner()->parent_->transform_->world_rotation_z_;

        const float theta = parent_rotation * GE_PI / 180.f;
        const float c = cosf(theta);
        const float s = sinf(theta);

        const float x = relative_location_.x * c - relative_location_.y * s + parent_location.x;
        const float y = relative_location_.x * s + relative_location_.y * c + parent_location.y;

        world_location_ = parent_location + Vector(x, y);
        world_rotation_z_ = parent_rotation + relative_rotation_z_;
    }
    else
    {
        world_location_ = relative_location_;
        world_rotation_z_ = relative_rotation_z_;
    }

    // 자식 Actor들의 Transform을 업데이트
    for (const auto& child : GetOwner()->children_)
    {
        child->transform_->UpdateTransform();
    }
}
