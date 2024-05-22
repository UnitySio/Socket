#include "GearJointComponent.h"
#include "box2d/box2d.h"
#include "../Engine/Level/World.h"
#include "../Engine/Actor/Actor.h"

GearJointComponent::GearJointComponent(Actor* owner, const std::wstring& kName):
	ActorComponent(owner, kName),
	jointDef_(new b2GearJointDef),
	joint_(nullptr),
	world_(World::Get()->physics_world_.get()),
	owner_(owner)
{
	jointDef_->bodyA = owner_->body_;
}

void GearJointComponent::EnableCollision(const bool& flag)
{
	jointDef_->collideConnected = flag;

	if (joint_ != nullptr)
		world_->DestroyJoint(joint_);
	joint_ = static_cast<b2GearJoint*>(world_->CreateJoint(jointDef_));
}

void GearJointComponent::ConnectedRigidBody(Actor* target)
{
	jointDef_->bodyB = target->body_;

	if (joint_ != nullptr)
		world_->DestroyJoint(joint_);
	joint_ = static_cast<b2GearJoint*>(world_->CreateJoint(jointDef_));
}

void GearJointComponent::SetRatio(const float& value)
{
	jointDef_->ratio = value;
	joint_->SetRatio(value);
}

inline void GearJointComponent::InitializeComponent()
{
	ActorComponent::InitializeComponent();
	
}

inline void GearJointComponent::UninitializeComponent()
{
	ActorComponent::UninitializeComponent();

}
