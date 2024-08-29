#include "pch.h"
#include "TransformComponent.h"

#include "Actor/Actor.h"
#include "Level/Level.h"
#include "Level/World.h"
#include "RigidBody2DComponent.h"

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
    
    b2BodyId body_id = GetOwner()->body_id_;
    if (!b2Body_IsValid(body_id)) return;
    
    if (!GetOwner()->parent_)
    {
        const b2Vec2 position = b2Body_GetPosition(body_id);
        relative_position_ = {position.x, position.y};

        const float angle = b2Rot_GetAngle(b2Body_GetRotation(body_id));
        relative_rotation_z_ = angle * 180.f / MATH_PI;

        UpdateTransform();
        return;
    }

    const RigidBody2DComponent* rigid_body = GetOwner()->GetComponent<RigidBody2DComponent>();
    if (!rigid_body || rigid_body->GetBodyType() == b2_kinematicBody) return;

    b2BodyId parent_body_id = GetOwner()->parent_->body_id_;

    const b2Vec2 position = b2InvMulTransforms(b2Body_GetTransform(parent_body_id), b2Body_GetTransform(body_id)).p;
    relative_position_ = {position.x, position.y};

    const float angle = b2Rot_GetAngle(b2Body_GetRotation(body_id)) - b2Rot_GetAngle(b2Body_GetRotation(parent_body_id));
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

        // 부모의 위치를 기준으로 자식의 위치를 상대 좌표로 변환
        Math::Vector2 local_position = position - parent_position;

        // 부모의 회전을 고려하여 상대 좌표 계산
        b2Rot rotation(-parent_rotation * MATH_PI / 180.f);
        b2Vec2 relative_position = b2InvRotateVector(rotation, {local_position.x, local_position.y});

        relative_position_ = {relative_position.x, relative_position.y};
    }
    else
    {
        relative_position_ = position;
    }
    
    UpdateTransform();
    
    b2BodyId body_id = GetOwner()->body_id_;
    if (b2Body_IsValid(body_id))
    {
        b2Body_SetTransform(body_id, {position.x, position.y}, b2MakeRot(world_rotation_z_ * MATH_PI / 180.f));
        b2Body_SetAwake(body_id, true);
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

    b2BodyId body_id = GetOwner()->body_id_;
    if (b2Body_IsValid(body_id))
    {
        b2Body_SetTransform(body_id, {world_position_.x, world_position_.y}, b2MakeRot(angle * MATH_PI / 180.f));
        b2Body_SetAwake(body_id, true);
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

    b2BodyId body_id = GetOwner()->body_id_;
    if (b2Body_IsValid(body_id))
    {
        b2Body_SetTransform(body_id, {world_position_.x, world_position_.y}, b2MakeRot(world_rotation_z_ * MATH_PI / 180.f));
        b2Body_SetAwake(body_id, true);
    }
}

void TransformComponent::SetRelativeRotationZ(float angle)
{
    relative_rotation_z_ = angle;
    UpdateTransform();

    b2BodyId body_id = GetOwner()->body_id_;
    if (b2Body_IsValid(body_id))
    {
        b2Body_SetTransform(body_id, {world_position_.x, world_position_.y}, b2MakeRot(world_rotation_z_ * MATH_PI / 180.f));
        b2Body_SetAwake(body_id, true);
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
        b2BodyId body_id = GetOwner()->body_id_;
        if (!b2Body_IsValid(body_id) || b2Body_GetType(body_id) != b2_staticBody)
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

        if (b2Body_IsValid(body_id) && b2Body_GetType(body_id) == b2_staticBody)
        {
            relative_position_ = world_position_ - GetOwner()->parent_->transform_->world_position_;
            relative_rotation_z_ = world_rotation_z_ - GetOwner()->parent_->transform_->world_rotation_z_;
        }

        if (const RigidBody2DComponent* rigid_body = GetOwner()->GetComponent<RigidBody2DComponent>())
        {
            if (rigid_body->GetBodyType() == b2_kinematicBody)
            {
                if (b2Body_IsValid(body_id))
                {
                    b2Body_SetTransform(body_id, {world_position_.x, world_position_.y}, b2MakeRot(world_rotation_z_ * MATH_PI / 180.f));
                    b2Body_SetAwake(body_id, true);
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
