#include "pch.h"
#include "BoxColliderComponent.h"

#include "Actor/Actor.h"
#include "box2d/box2d.h"
#include "box2d/collision.h"

BoxColliderComponent::BoxColliderComponent(Actor* owner, const std::wstring& kName) :
    ColliderComponent(owner, kName),
    size_(Math::Vector2::One())
{
    SetBox();
}

void BoxColliderComponent::SetOffset(const Math::Vector2& kOffset)
{
    ColliderComponent::SetOffset(kOffset);
    
    SetBox();
}

void BoxColliderComponent::SetSize(Math::Vector2 size)
{
    size_ = size;
    SetBox();
}

void BoxColliderComponent::SetTrigger(bool is_trigger)
{
    if (!b2Shape_IsValid(shape_id_)) return;

    b2Polygon box = b2Shape_GetPolygon(shape_id_);
    
    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = b2Shape_GetDensity(shape_id_);
    shape_def.friction = b2Shape_GetFriction(shape_id_);
    shape_def.filter = b2Shape_GetFilter(shape_id_);
    shape_def.isSensor = is_trigger;

    b2DestroyShape(shape_id_);
    shape_id_ = b2CreatePolygonShape(GetOwner()->body_id_, &shape_def, &box);
}

void BoxColliderComponent::SetBox()
{
    b2Polygon box = b2MakeOffsetBox(size_.x * .5f, size_.y * .5f, {offset_.x, offset_.y}, 0.f);

    if (b2Shape_IsValid(shape_id_))
    {
        b2Shape_SetPolygon(shape_id_, &box);
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

        shape_id_ = b2CreatePolygonShape(GetOwner()->body_id_, &shape_def, &box);
    }
}
