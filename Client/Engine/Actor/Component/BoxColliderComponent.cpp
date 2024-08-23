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

void BoxColliderComponent::SetBox()
{
    const Math::Vector2 half_size = size_ * .5f;

    b2Polygon box = b2MakeOffsetBox(half_size.x, half_size.y, {offset_.x, offset_.y}, 0.f);

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
