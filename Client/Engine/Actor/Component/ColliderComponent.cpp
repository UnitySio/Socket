﻿#include "pch.h"
#include "ColliderComponent.h"

#include "TransformComponent.h"
#include "Actor/Actor.h"
#include "box2d/box2d.h"
#include "Math/Bounds.h"

ColliderComponent::ColliderComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    offset_(Math::Vector2::Zero()),
    material_(),
    is_trigger_(false)
{
}

void ColliderComponent::InitializeComponent()
{
    ActorComponent::InitializeComponent();
    
    if (!b2Body_IsValid(GetOwner()->body_id_)) GetOwner()->CreateBody();
    SetShape();
    
    SetMaterialIntermal(); // 물리 메테리얼을 설정합니다.
}

void ColliderComponent::SetOffset(const Math::Vector2& kOffset)
{
    offset_ = kOffset;

    if (HasBegunPlay())
    {
        SetShape();
    }
}

void ColliderComponent::SetMaterial(const PhysicsMaterial2D& kMaterial)
{
    material_ = kMaterial;

    if (HasBegunPlay())
    {
        SetMaterialIntermal();
    }
}

void ColliderComponent::SetTrigger(bool is_trigger)
{
    is_trigger_ = is_trigger;

    if (HasBegunPlay())
    {
        SetTriggerInternal();
    }
}

const Bounds& ColliderComponent::GetBounds()
{
    if (!b2Shape_IsValid(shape_id_)) return Bounds();
    
    b2AABB aabb = b2Shape_GetAABB(shape_id_);

    Bounds bounds;
    bounds.center = {b2AABB_Center(aabb).x, b2AABB_Center(aabb).y};
    bounds.size = {b2AABB_Extents(aabb).x * 2.f, b2AABB_Extents(aabb).y * 2.f};
    bounds.extents = {b2AABB_Extents(aabb).x, b2AABB_Extents(aabb).y};
    bounds.min = {aabb.lowerBound.x, aabb.lowerBound.y};
    bounds.max = {aabb.upperBound.x, aabb.upperBound.y};

    return bounds;
}

void ColliderComponent::SetShape()
{
}

void ColliderComponent::SetTriggerInternal()
{
}

void ColliderComponent::SetMaterialIntermal()
{
    if (!b2Shape_IsValid(shape_id_)) return;

    b2Shape_SetFriction(shape_id_, material_.friction);
    b2Shape_SetRestitution(shape_id_, material_.bounciness);
}
