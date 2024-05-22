#include "HingeJointComponent.h"
#include "box2d/box2d.h"
#include "../Engine/Level/World.h"
#include "../Engine/Actor/Actor.h"

HingeJointComponent::HingeJointComponent(Actor* owner, const std::wstring& kName) :
	ActorComponent(owner, kName),
	owner_(owner),
	jointDef_(new b2RevoluteJointDef),
	world_(World::Get()->physics_world_.get()),
	joint_(nullptr)
{
	jointDef_->bodyA = owner_->body_;
	jointDef_->enableLimit = false;
	jointDef_->enableMotor = true;
	jointDef_->maxMotorTorque = 10.0f;
}

void HingeJointComponent::ConnectedRigidBody(Actor* target)
{
	jointDef_->bodyB = target->body_;
	jointDef_->Initialize(jointDef_->bodyA, jointDef_->bodyB, jointDef_->bodyB->GetWorldCenter());

	if (joint_ != nullptr)
		world_->DestroyJoint(joint_);
	joint_ = static_cast<b2RevoluteJoint*>(world_->CreateJoint(jointDef_));
}

void HingeJointComponent::SetLimits(const float& lower, const float& upper)
{
	joint_->SetLimits(lower, upper);
}

void HingeJointComponent::SetMaxMotorTorque(const float& value)
{
	jointDef_->maxMotorTorque = value;
	
	if (joint_ != nullptr)
		joint_->SetMaxMotorTorque(value);
}

void HingeJointComponent::SetMotorSpeed(const float& value)
{
	jointDef_->motorSpeed = value;

	if (joint_ != nullptr)
		joint_->SetMotorSpeed(value);
}

inline void HingeJointComponent::InitializeComponent()
{
	ActorComponent::InitializeComponent();
}

inline void HingeJointComponent::UninitializeComponent()
{
	ActorComponent::UninitializeComponent();
	delete jointDef_;
	if (joint_ != nullptr)
	{
		world_->DestroyJoint(joint_);
		joint_ = nullptr;
	}
}

