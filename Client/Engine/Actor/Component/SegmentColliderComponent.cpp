#include "pch.h"
#include "SegmentColliderComponent.h"

#include "Actor/Actor.h"
#include "box2d/box2d.h"
#include "box2d/collision.h"

SegmentColliderComponent::SegmentColliderComponent(Actor* actor, const std::wstring& kName) :
    ColliderComponent(actor, kName),
    start_(Math::Vector2::Zero()),
    end_(Math::Vector2::Right())
{
    SetShape();
}

void SegmentColliderComponent::SetSegment(const Math::Vector2& start, const Math::Vector2& end)
{
    start_ = start;
    end_ = end;

    SetShape();
}

void SegmentColliderComponent::SetTrigger(bool is_trigger)
{
    b2Segment segment = b2Shape_GetSegment(shape_id_);
    
    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = b2Shape_GetDensity(shape_id_);
    shape_def.friction = b2Shape_GetFriction(shape_id_);
    shape_def.restitution = b2Shape_GetRestitution(shape_id_);
    shape_def.filter = b2Shape_GetFilter(shape_id_);
    shape_def.isSensor = is_trigger;

    b2DestroyShape(shape_id_);
    shape_id_ = b2CreateSegmentShape(GetOwner()->body_id_, &shape_def, &segment);
}

void SegmentColliderComponent::SetShape()
{
    b2Segment segment = {{start_.x, start_.y}, {end_.x, end_.y}};

    if (b2Shape_IsValid(shape_id_))
    {
        b2Shape_SetSegment(shape_id_, &segment);
    }
    else
    {
        b2Filter filter = b2DefaultFilter();
        filter.categoryBits = GetOwner()->GetLayer();
        filter.maskBits = ProjectSettings::kLayerCollisionMatrix.at(GetOwner()->GetLayer());

        b2ShapeDef shape_def = b2DefaultShapeDef();
        shape_def.density = 1.f;
        shape_def.friction = 0.2f;
        shape_def.restitution = 0.0f;
        shape_def.filter = filter;
        shape_def.userData = this;

        shape_id_ = b2CreateSegmentShape(GetOwner()->body_id_, &shape_def, &segment);
    }
}
