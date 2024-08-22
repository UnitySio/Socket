#include "pch.h"
#include "ColliderComponent.h"

#include "TransformComponent.h"
#include "Actor/Actor.h"

ColliderComponent::ColliderComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    offset_(Math::Vector2::Zero())
{
    if (!b2Body_IsValid(GetOwner()->body_id_)) GetOwner()->CreateBody();
}

void ColliderComponent::SetTrigger(bool isTrigger)
{
    if (!b2Shape_IsValid(shape_id_)) return;
    b2Shape_EnableSensorEvents(shape_id_, isTrigger);
}

void ColliderComponent::SetOffset(const Math::Vector2& kOffset)
{
    offset_ = kOffset;
}

const Bounds& ColliderComponent::GetBounds()
{
    b2AABB aabb = b2Shape_GetAABB(shape_id_);

    Bounds bounds;
    bounds.center = {b2AABB_Center(aabb).x, b2AABB_Center(aabb).y};
    bounds.size = {b2AABB_Extents(aabb).x * 2.f, b2AABB_Extents(aabb).y * 2.f};
    bounds.extents = {b2AABB_Extents(aabb).x, b2AABB_Extents(aabb).y};
    bounds.min = {aabb.lowerBound.x, aabb.lowerBound.y};
    bounds.max = {aabb.upperBound.x, aabb.upperBound.y};

    return bounds;
}
