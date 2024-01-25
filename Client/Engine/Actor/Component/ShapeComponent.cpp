#include "ShapeComponent.h"

#include "box2d/b2_fixture.h"
#include "../Actor.h"

ShapeComponent::ShapeComponent(Actor* actor) : Component(actor)
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
