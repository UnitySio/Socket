#include "DistanceJointComponent.h"
#include "box2d/box2d.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include <memory>
#include "Actor/Actor.h"
#include "../Engine/Level/World.h"


DistanceJointComponent::DistanceJointComponent(Actor* owner, const std::wstring& kName) :
	BaseJointComponent(owner, kName),
	owner_(owner),
	jointBody_(nullptr)
{
}


inline void DistanceJointComponent::InitializeComponent()
{
	ActorComponent::InitializeComponent();
	
}

inline void DistanceJointComponent::UninitializeComponent()
{
	ActorComponent::UninitializeComponent();
	
	if (joint_ != nullptr)
	{
		delete joint_;
		joint_ = nullptr;
	}
}

void DistanceJointComponent::SetDefaultProperties()
{
	jointDef_->collideConnected = false;
	jointDef_->maxLength = 3.0f;
	jointDef_->bodyA = owner_->body_;
	jointDef_->bodyB = target_->body_;
}

void DistanceJointComponent::CreateJoint()
{
	auto temp = static_cast<b2DistanceJoint*>(world_->CreateJoint(jointDef_));
	if(jointBody_ == nullptr)
		jointBody_ = new DistanceJoint(this, temp);
	
	else
		jointBody_->joint_ = temp;
}



void DistanceJointComponent::DistanceJoint::EnableCollision(const bool& flag)
{
	component_->jointDef_->collideConnected = flag;
	JOINT_RESETOR(DistanceJointComponent)
}

void DistanceJointComponent::DistanceJoint::ConnectedRigidBody(Actor* target)
{
	component_->jointDef_->bodyB = target->body_;
	JOINT_RESETOR(DistanceJointComponent)
}
