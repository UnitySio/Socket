﻿#include "pch.h"
#include "TransformComponent.h"

#include "Actor/Actor.h"
#include "Level/Level.h"
#include "Level/World.h"
#include "RigidBody2DComponent.h"

TransformComponent::TransformComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    position_(Math::Vector2::Zero()),
    scale_(Math::Vector2::One()),
    angle_(0.f)
{
}

void TransformComponent::PhysicsTickComponent(float delta_time)
{
    ActorComponent::PhysicsTickComponent(delta_time);
    
    b2BodyId  body_id = GetOwner()->body_id_;
    if (b2Body_IsValid(body_id) && b2Body_GetType(body_id) != b2_staticBody)
    {
        const b2Vec2& position = b2Body_GetPosition(body_id);
        position_ = {position.x, position.y};

        const b2Rot& rotation = b2Body_GetRotation(body_id);
        angle_ = b2Rot_GetAngle(rotation) * 180.f / MATH_PI;
    }
}

void TransformComponent::SetPosition(const Math::Vector2& position)
{
    position_ = position;

    b2BodyId  body_id = GetOwner()->body_id_;
    if (b2Body_IsValid(body_id))
    {
        b2Body_SetTransform(body_id, {position.x, position.y}, b2MakeRot(angle_ * MATH_PI / 180.f));
        b2Body_SetAwake(body_id, true);
    }
}

void TransformComponent::SetAngle(float angle)
{
    angle_ = angle;
    
    b2BodyId  body_id = GetOwner()->body_id_;
    if (b2Body_IsValid(body_id))
    {
        b2Body_SetTransform(body_id, {position_.x, position_.y}, b2MakeRot(angle * MATH_PI / 180.f));
        b2Body_SetAwake(body_id, true);
    }
}

void TransformComponent::SetScale(const Math::Vector2& scale)
{
    scale_ = scale;
}

void TransformComponent::Translate(const Math::Vector2& translation)
{
    Math::Vector2 new_position = position_ + translation;
    SetPosition(new_position);
}

Math::Vector2 TransformComponent::GetRightVector() const
{
    const float theta = angle_ * MATH_PI / 180.f;
    const float c = cosf(theta);
    const float s = sinf(theta);

    return {c, s};
}

Math::Vector2 TransformComponent::GetUpVector() const
{
    const float theta = angle_ * MATH_PI / 180.f;
    const float c = cosf(theta);
    const float s = sinf(theta);

    return {-s, c};
}
