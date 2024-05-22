#include "GearJointComponent.h"
#include "box2d/box2d.h"
#include "../Engine/Level/World.h"

GearJointComponent::GearJointComponent(Actor* owner, const std::wstring& kName):
	ActorComponent(owner, kName),
	jointDef_(new b2GearJointDef),
	joint_(nullptr),
	world_(World::Get()->physics_world_.get()),
	owner_(owner)
{
	
}

inline void GearJointComponent::InitializeComponent()
{
	ActorComponent::InitializeComponent();
}

inline void GearJointComponent::UninitializeComponent()
{
}
