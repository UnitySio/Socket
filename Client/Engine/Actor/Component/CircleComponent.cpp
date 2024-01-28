#include "CircleComponent.h"

#include "box2d/b2_circle_shape.h"
#include "box2d/b2_fixture.h"
#include "../Actor.h"

CircleComponent::CircleComponent(Actor* owner, const std::wstring& name) : ShapeComponent(owner, name)
{
    b2CircleShape circle;
    circle.m_radius = 1.f;

    b2FixtureDef fixture_def;
    fixture_def.shape = &circle;

    fixture_ = owner_->GetBody()->CreateFixture(&fixture_def);
}

void CircleComponent::SetRadius(float radius, b2Vec2 center)
{
    b2CircleShape circle;
    circle.m_radius = radius;
    circle.m_p = center;

    b2FixtureDef fixture_def;
    fixture_def.shape = &circle;
    fixture_def.density = fixture_->GetDensity();
    fixture_def.friction = fixture_->GetFriction();
    
    owner_->GetBody()->DestroyFixture(fixture_);
    fixture_ = owner_->GetBody()->CreateFixture(&fixture_def);
}
