﻿#include "pch.h"
#include "TransformComponent.h"

#include "Actor/Actor.h"
#include "box2d/b2_body.h"
#include "Level/Level.h"
#include "Level/World.h"
#include "RigidBodyComponent.h"

TransformComponent::TransformComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    world_position_(Math::Vector2::Zero()),
    world_scale_(Math::Vector2::One()),
    relative_position_(Math::Vector2::Zero()),
    relative_scale_(Math::Vector2::One()),
    world_rotation_z_(0.f),
    relative_rotation_z_(0.f)
{
}

void TransformComponent::TickComponent(float delta_time)
{
    ActorComponent::TickComponent(delta_time);

    const b2Body* body = GetOwner()->body_;
    if (!body || body->GetType() == b2_staticBody) return;
    
    if (!GetOwner()->parent_)
    {
        const b2Vec2 position = body->GetPosition();
        relative_position_ = {position.x, position.y};

        const float angle = body->GetAngle();
        relative_rotation_z_ = angle * 180.f / MATH_PI;

        UpdateTransform();
        return;
    }

    const RigidBodyComponent* rigid_body = GetOwner()->GetComponent<RigidBodyComponent>();
    if (!rigid_body || rigid_body->GetBodyType() == b2_kinematicBody) return;

    const b2Vec2 position = b2MulT(GetOwner()->parent_->body_->GetTransform(), body->GetTransform().p);
    relative_position_ = {position.x, position.y};

    const float angle = body->GetAngle() - GetOwner()->parent_->body_->GetAngle();
    relative_rotation_z_ = angle * 180.f / MATH_PI; 
    
    UpdateTransform();
}

void TransformComponent::SetWorldPosition(Math::Vector2 position)
{
    world_position_ = position;
    if (GetOwner()->parent_)
    {
        const Math::Vector2 parent_position = GetOwner()->parent_->transform_->world_position_;
        const float parent_rotation = GetOwner()->parent_->transform_->world_rotation_z_;

        const float theta = -parent_rotation * MATH_PI / 180.f;
        const float c = cosf(theta);
        const float s = sinf(theta);

        const float x = (position.x - parent_position.x) * c - (position.y - parent_position.y) * s;
        const float y = (position.x - parent_position.x) * s + (position.y - parent_position.y) * c;

        relative_position_ = {x, y};
    }
    else
    {
        relative_position_ = position;
    }
    
    UpdateTransform();

    if (b2Body* body = GetOwner()->body_)
    {
        body->SetTransform({position.x, position.y}, world_rotation_z_ * MATH_PI / 180.f);
        body->SetAwake(true);
    }
}

void TransformComponent::SetWorldRotationZ(float angle)
{
    world_rotation_z_ = angle;
    if (GetOwner()->parent_)
    {
        const float parent_rotation = GetOwner()->parent_->transform_->world_rotation_z_;
        relative_rotation_z_ = angle - parent_rotation;
    }
    else
    {
        relative_rotation_z_ = angle;
    }
    
    UpdateTransform();

    if (b2Body* body = GetOwner()->body_)
    {
        body->SetTransform({world_position_.x, world_position_.y}, angle * MATH_PI / 180.f);
        body->SetAwake(true);
    }
}

void TransformComponent::SetWorldScale(Math::Vector2 scale)
{
    world_scale_ = scale;
    if (GetOwner()->parent_)
    {
        const Math::Vector2 parent_scale = GetOwner()->parent_->transform_->world_scale_;
        relative_scale_ = scale / parent_scale;
    }
    else
    {
        relative_scale_ = scale;
    }
    
    UpdateTransform();
}


void TransformComponent::SetRelativePosition(Math::Vector2 position)
{
    relative_position_ = position;
    UpdateTransform();

    if (b2Body* body = GetOwner()->body_)
    {
        body->SetTransform({world_position_.x, world_position_.y}, world_rotation_z_ * MATH_PI / 180.f);
        body->SetAwake(true);
    }
}

void TransformComponent::SetRelativeRotationZ(float angle)
{
    relative_rotation_z_ = angle;
    UpdateTransform();

    if (b2Body* body = GetOwner()->body_)
    {
        body->SetTransform({world_position_.x, world_position_.y}, world_rotation_z_ * MATH_PI / 180.f);
        body->SetAwake(true);
    }
}

void TransformComponent::SetRelativeScale(Math::Vector2 scale)
{
    relative_scale_ = scale;
    UpdateTransform();
}

Math::Vector2 TransformComponent::GetRightVector() const
{
    const float theta = relative_rotation_z_ * MATH_PI / 180.f;
    const float c = cosf(theta);
    const float s = sinf(theta);

    return {c, s};
}

Math::Vector2 TransformComponent::GetUpVector() const
{
    const float theta = relative_rotation_z_ * MATH_PI / 180.f;
    const float c = cosf(theta);
    const float s = sinf(theta);

    return {-s, c};
}

void TransformComponent::UpdateTransform()
{
    if (GetOwner()->parent_)
    {
        const b2Body* body = GetOwner()->body_;
        if (!body || body->GetType() != b2_staticBody)
        {
            Math::Vector2 parent_position = GetOwner()->parent_->transform_->world_position_;
            const float parent_rotation = GetOwner()->parent_->transform_->world_rotation_z_;

            const float theta = parent_rotation * MATH_PI / 180.f;
            const float c = cosf(theta);
            const float s = sinf(theta);

            const float x = relative_position_.x * c - relative_position_.y * s;
            const float y = relative_position_.x * s + relative_position_.y * c;

            world_position_ = parent_position + Math::Vector2(x, y);
            world_rotation_z_ = parent_rotation + relative_rotation_z_;
        }

        if (body && body->GetType() == b2_staticBody)
        {
            relative_position_ = world_position_ - GetOwner()->parent_->transform_->world_position_;
            relative_rotation_z_ = world_rotation_z_ - GetOwner()->parent_->transform_->world_rotation_z_;
        }

        if (const RigidBodyComponent* rigid_body = GetOwner()->GetComponent<RigidBodyComponent>())
        {
            if (rigid_body->GetBodyType() == b2_kinematicBody)
            {
                if (b2Body* body = GetOwner()->body_)
                {
                    body->SetTransform({world_position_.x, world_position_.y}, world_rotation_z_ * MATH_PI / 180.f);
                    body->SetAwake(true);
                }
            }
        }

        Math::Vector2 parent_scale = GetOwner()->parent_->transform_->world_scale_;
        world_scale_ = parent_scale * relative_scale_;
    }
    else
    {
        world_position_ = relative_position_;
        world_rotation_z_ = relative_rotation_z_;
        world_scale_ = relative_scale_;
    }

    // 자식 Actor들의 Transform을 업데이트
    for (const auto& child : GetOwner()->children_)
    {
        child->transform_->UpdateTransform();
    }
}
