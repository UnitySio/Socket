#include "ShapeComponent.h"

#include "box2d/b2_fixture.h"
#include "../Actor.h"

ShapeComponent::ShapeComponent(Actor* actor, const std::wstring& name) :
    ActorComponent(actor, name),
    fixture_(nullptr)
{
}

void ShapeComponent::SetDensity(float density)
{
    fixture_->SetDensity(density);
    owner_->GetBody()->ResetMassData();
}

void ShapeComponent::SetFriction(float friction)
{
    fixture_->SetFriction(friction);
}

void ShapeComponent::SetRestitution(float restitution)
{
    fixture_->SetRestitution(restitution);
}

void ShapeComponent::SetRestitutionThreshold(float threshold)
{
    fixture_->SetRestitutionThreshold(threshold);
}

void ShapeComponent::SetTrigger(bool trigger)
{
    fixture_->SetSensor(trigger);
}
