﻿#include "CircleComponent.h"

#include "../../../Actor.h"
#include "box2d/b2_body.h"
#include "box2d/b2_circle_shape.h"

CircleComponent::CircleComponent(Actor* owner, const std::wstring& kName) :
    ShapeComponent(owner, kName),
    radius_(0.f)
{
}

void CircleComponent::SetCircleRadius(float radius)
{
    SceneComponent* root = owner_->GetRootComponent();
    assert(root);

    radius_ = radius;

    b2CircleShape circle;
    circle.m_radius = radius;

    CreateFixture(&circle);
}

void CircleComponent::UpdateTransform()
{
    SceneComponent* root = owner_->GetRootComponent();
    b2Body* body = root->GetBody();

    b2Vec2 location = body->GetLocalPoint(GetWorldLocation());

    b2CircleShape circle;
    circle.m_radius = radius_;
    circle.m_p = location;

    CreateFixture(&circle);
    UpdateChildTransforms();
}