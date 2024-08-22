#include "pch.h"
#include "CircleColliderComponent.h"

#include "Actor/Actor.h"
#include "box2d/box2d.h"
#include "box2d/collision.h"

CircleColliderComponent::CircleColliderComponent(Actor* owner, const std::wstring& kName) :
    ColliderComponent(owner, kName),
    radius_(.5f)
{
    SetCircle();
}

void CircleColliderComponent::SetOffset(const Math::Vector2& kOffset)
{
    ColliderComponent::SetOffset(kOffset);

    SetCircle();
}

void CircleColliderComponent::SetRadius(float radius)
{
    radius_ = radius;
    SetCircle();
}

void CircleColliderComponent::SetCircle()
{
    b2Circle circle;
    circle.center = {offset_.x, offset_.y};
    circle.radius = radius_;
    
    if (b2Shape_IsValid(shape_id_))
    {
        b2Shape_SetCircle(shape_id_, &circle);
    }
    else
    {
        b2Filter filter;
        filter.categoryBits = GetOwner()->GetLayer();
        filter.maskBits = ProjectSettings::kLayerCollisionMatrix.at(GetOwner()->GetLayer());
        
        b2ShapeDef shape_def = b2DefaultShapeDef();
        shape_def.density = 1.f;
        shape_def.friction = .3f;
        shape_def.filter = filter;

        shape_id_ = b2CreateCircleShape(GetOwner()->body_id_, &shape_def, &circle);
    }
}
