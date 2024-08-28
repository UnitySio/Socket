#include "pch.h"
#include "CircleColliderComponent.h"

#include "Actor/Actor.h"
#include "box2d/box2d.h"
#include "box2d/collision.h"

CircleColliderComponent::CircleColliderComponent(Actor* owner, const std::wstring& kName) :
    ColliderComponent(owner, kName),
    radius_(.5f)
{
    SetShape();
}

void CircleColliderComponent::SetOffset(const Math::Vector2& kOffset)
{
    ColliderComponent::SetOffset(kOffset);

    SetShape();
}

void CircleColliderComponent::SetRadius(float radius)
{
    radius_ = radius;
    SetShape();
}

void CircleColliderComponent::SetTrigger(bool is_trigger)
{
    if (!b2Shape_IsValid(shape_id_)) return;

    b2Circle circle = b2Shape_GetCircle(shape_id_);

    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = b2Shape_GetDensity(shape_id_);
    shape_def.friction = b2Shape_GetFriction(shape_id_);
    shape_def.restitution = b2Shape_GetRestitution(shape_id_);
    shape_def.filter = b2Shape_GetFilter(shape_id_);
    shape_def.isSensor = is_trigger;

    b2DestroyShape(shape_id_);
    shape_id_ = b2CreateCircleShape(GetOwner()->body_id_, &shape_def, &circle);
}

void CircleColliderComponent::SetShape()
{
    b2Circle circle = {
        {offset_.x, offset_.y},
        radius_
    };
    
    if (b2Shape_IsValid(shape_id_))
    {
        b2Shape_SetCircle(shape_id_, &circle);
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

        shape_id_ = b2CreateCircleShape(GetOwner()->body_id_, &shape_def, &circle);
    }
}
