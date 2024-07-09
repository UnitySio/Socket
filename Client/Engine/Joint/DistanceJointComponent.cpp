#include "DistanceJointComponent.h"
#include "box2d/box2d.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include <memory>
#include "Actor/Actor.h"
#include "../Engine/Level/World.h"


DistanceJointComponent::DistanceJointComponent(Actor* owner, const std::wstring& kName) :
	BaseJointComponent(owner, kName),
	jointBody_(nullptr)
{
	owner_ = owner;
}


inline void DistanceJointComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
}

inline void DistanceJointComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
	
	if (jointBody_ != nullptr)
	{
		delete jointBody_;
		jointBody_ = nullptr;
	}
}

void DistanceJointComponent::SetDefaultProperties(const bool& flag)
{
	jointDef_->collideConnected = false;
	jointDef_->maxLength = 3.0f;
	jointDef_->bodyA = owner_->body_;
	jointDef_->bodyB = target_->body_;
	
	if (jointBody_ == nullptr)
	{
		jointBody_ = new DistanceJoint(this, nullptr, flag);
	}
		
}

void DistanceJointComponent::CreateJoint()
{
	auto temp = static_cast<b2DistanceJoint*>(world_->CreateJoint(jointDef_));
	if(jointBody_ == nullptr)
		jointBody_ = new DistanceJoint(this, temp);
	
	else
		jointBody_->joint_ = temp;
}



void DistanceJointComponent::DistanceJoint::CreateJoint(const bool& flag)
{
	if (flag)
		RESERVE(DistanceJointComponent)
	

	else if (!flag)
	{
		if (joint_ != nullptr)
			DESTROY
		RESERVE(DistanceJointComponent)
	}
}

void DistanceJointComponent::DistanceJoint::EnableCollision(const bool& flag)
{
	JOINT_DEF->collideConnected = flag;
	JOINT_RESETOR(DistanceJointComponent)
}

void DistanceJointComponent::DistanceJoint::ConnectedRigidBody(Actor* target)
{
	JOINT_DEF->bodyB = target->body_;
	JOINT_RESETOR(DistanceJointComponent)
}

void DistanceJointComponent::DistanceJoint::Anchor(const Math::Vector2& pos)
{
	JOINT_DEF->localAnchorA = b2Vec2(pos.x, pos.y);
	JOINT_RESETOR(DistanceJointComponent)
}

void DistanceJointComponent::DistanceJoint::ConnectedAnchor(const Math::Vector2& pos)
{
	JOINT_DEF->localAnchorB = b2Vec2(pos.x, pos.y);
	JOINT_RESETOR(DistanceJointComponent)
}

void DistanceJointComponent::DistanceJoint::Distance(const float& value)
{
	JOINT_DEF->length = value;
	joint_->SetLength(value);
}

void DistanceJointComponent::DistanceJoint::SetMaxDistance(const float& value)
{
	JOINT_DEF->maxLength = value;
	joint_->SetMaxLength(value);
}

void DistanceJointComponent::DistanceJoint::SetMinDistance(const float& value)
{
	JOINT_DEF->minLength = value;
	joint_->SetMinLength(value);
}

void DistanceJointComponent::DistanceJoint::SetDampingRatio(const float& value)
{
	JOINT_DEF->damping = value;
	joint_->SetDamping(value);
	
}

void DistanceJointComponent::DistanceJoint::SetStiffness(const float& value)
{
	JOINT_DEF->stiffness = value;
	joint_->SetStiffness(value);
}
