#include "FrictionJointComponent.h"
#include "box2d/box2d.h"
#include "../Engine/Level/World.h"
#include "../Engine/Actor/Actor.h"

FrictionJointComponent::FrictionJointComponent(Actor* owner, const std::wstring& kName):
	ActorComponent(owner, kName),
	owner_(owner),
	jointDef_(new b2FrictionJointDef),
	world_(World::Get()->physics_world_.get()),
	joint_(nullptr)
{
	jointDef_->bodyA = owner_->body_;
}

inline void FrictionJointComponent::InitializeComponent()
{
	ActorComponent::InitializeComponent();
	if (jointDef_->bodyB != nullptr)
		joint_ = static_cast<b2FrictionJoint*>(world_->CreateJoint(jointDef_));
}

inline void FrictionJointComponent::UninitializeComponent()
{
	ActorComponent::UninitializeComponent();
	delete jointDef_;
	if (joint_ != nullptr)
	{
		world_->DestroyJoint(joint_);
		joint_ = nullptr;
	}
}

void FrictionJointComponent::EnableCollision(const bool& flag)
{
	jointDef_->collideConnected = flag;

	if (joint_ != nullptr)
		joint_ = static_cast<b2FrictionJoint*>(world_->CreateJoint(jointDef_));
}

void FrictionJointComponent::ConnectedRigidBody(Actor* target)
{
	jointDef_->bodyB = target->body_;

	if (joint_ != nullptr)
		joint_ = static_cast<b2FrictionJoint*>(world_->CreateJoint(jointDef_));
}

void FrictionJointComponent::Anchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorA = b2Vec2(pos.x, pos.y);
	if (joint_ != nullptr)
		joint_ = static_cast<b2FrictionJoint*>(world_->CreateJoint(jointDef_));
}

void FrictionJointComponent::ConnectedAnchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorB = b2Vec2(pos.x, pos.y);
	if (joint_ != nullptr)
		joint_ = static_cast<b2FrictionJoint*>(world_->CreateJoint(jointDef_));
}

void FrictionJointComponent::MaxForce(const float& value)
{
	jointDef_->maxForce = value;
	joint_->SetMaxForce(value);
}

void FrictionJointComponent::MaxTorque(const float& value)
{
	jointDef_->maxTorque = value;
	joint_->SetMaxTorque(value);
}



