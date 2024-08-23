﻿#include "pch.h"
#include "CapsuleColliderComponent.h"

#include "Actor/Actor.h"
#include "box2d/box2d.h"
#include "box2d/collision.h"

CapsuleColliderComponent::CapsuleColliderComponent(Actor* owner, const std::wstring& kName) :
    ColliderComponent(owner, kName),
    size_(Math::Vector2::One())
{
}

void CapsuleColliderComponent::SetOffset(const Math::Vector2& kOffset)
{
    ColliderComponent::SetOffset(kOffset);

    SetCapsule();
}

void CapsuleColliderComponent::SetSize(Math::Vector2 size)
{
    size_ = size;
    SetCapsule();
}

void CapsuleColliderComponent::SetTrigger(bool is_trigger)
{
    if (!b2Shape_IsValid(shape_id_)) return;

    b2Capsule capsule = b2Shape_GetCapsule(shape_id_);
    
    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = b2Shape_GetDensity(shape_id_);
    shape_def.friction = b2Shape_GetFriction(shape_id_);
    shape_def.filter = b2Shape_GetFilter(shape_id_);
    shape_def.isSensor = is_trigger;

    b2DestroyShape(shape_id_);
    shape_id_ = b2CreateCapsuleShape(GetOwner()->body_id_, &shape_def, &capsule);
}

void CapsuleColliderComponent::SetCapsule()
{
    b2Capsule capsule = {
        {offset_.x, offset_.y - size_.y},
        {offset_.x, offset_.y + size_.y},
        size_.x * .5f
    };

    if (b2Shape_IsValid(shape_id_))
    {
        b2Shape_SetCapsule(shape_id_, &capsule);
    }
    else
    {
        b2Filter filter = b2DefaultFilter();
        filter.categoryBits = GetOwner()->GetLayer();
        filter.maskBits = ProjectSettings::kLayerCollisionMatrix.at(GetOwner()->GetLayer());
        
        b2ShapeDef shape_def = b2DefaultShapeDef();
        shape_def.density = 1.f;
        shape_def.friction = .3f;
        shape_def.filter = filter;
    
        shape_id_ = b2CreateCapsuleShape(GetOwner()->body_id_, &shape_def, &capsule);
    }
}
