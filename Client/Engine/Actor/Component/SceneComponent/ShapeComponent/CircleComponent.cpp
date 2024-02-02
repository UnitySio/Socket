#include "CircleComponent.h"

#include "box2d/b2_circle_shape.h"
#include "box2d/b2_fixture.h"

CircleComponent::CircleComponent(Actor* owner, const std::wstring& kName) : ShapeComponent(owner, kName)
{
    b2CircleShape circle;
    circle.m_radius = 1.f;

    b2FixtureDef fixture_def;
    fixture_def.shape = &circle;

    fixture_ = body_->CreateFixture(&fixture_def);
}

void CircleComponent::SetCircleRadius(float radius)
{
    b2CircleShape circle;
    circle.m_radius = radius;

    b2FixtureDef fixture_def;
    fixture_def.shape = &circle;
    fixture_def.density = fixture_->GetDensity();
    fixture_def.friction = fixture_->GetFriction();

    body_->DestroyFixture(fixture_);
    fixture_ = body_->CreateFixture(&fixture_def);
}
