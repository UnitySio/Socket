#include "pch.h"
#include "CircleColliderComponent.h"

#include "box2d/b2_circle_shape.h"

CircleColliderComponent::CircleColliderComponent(Actor* owner, const std::wstring& kName) :
    Super(owner, kName),
    radius_(.5f)
{
    SetCircle();
}

void CircleColliderComponent::SetOffset(const Math::Vector2& kOffset)
{
    Super::SetOffset(kOffset);

    SetCircle();
}

void CircleColliderComponent::SetRadius(float radius)
{
    radius_ = radius;
    SetCircle();
}

void CircleColliderComponent::SetCircle()
{
    b2CircleShape circle;
    circle.m_p = {offset_.x, offset_.y};
    circle.m_radius = radius_;

    CreateFixture(&circle);
}
