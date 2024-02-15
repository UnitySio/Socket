#include "CircleColliderComponent.h"

#include "../../../Actor.h"
#include "box2d/b2_body.h"
#include "box2d/b2_circle_shape.h"

CircleColliderComponent::CircleColliderComponent(Actor* owner, const std::wstring& kName) :
    ColliderComponent(owner, kName),
    radius_(0.f)
{
}

void CircleColliderComponent::SetCircleRadius(float radius)
{
    radius_ = radius;

    b2CircleShape circle;
    circle.m_radius = radius;

    CreateFixture(&circle);
}

void CircleColliderComponent::UpdateTransform()
{
    b2Body* body = owner_->body_;

    b2Vec2 location = body->GetLocalPoint(GetWorldLocation());

    b2CircleShape circle;
    circle.m_radius = radius_;
    circle.m_p = location;

    CreateFixture(&circle);
    UpdateChildTransforms();
}
