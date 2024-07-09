#include "MotorJointComponent.h"

MotorJointComponent::MotorJointComponent(Actor* owner, const std::wstring& kName):
	Super(owner, kName),
	jointBody_(nullptr)
{
	owner_ = owner;
}

void MotorJointComponent::CreateJoint()
{
	auto temp = static_cast<b2MotorJoint*>(world_->CreateJoint(jointDef_));
	if (jointBody_ == nullptr)
		jointBody_ = new MotorJoint(this, temp);

	else
		jointBody_->joint_ = temp;
}

inline void MotorJointComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

inline void MotorJointComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
	if (jointBody_ != nullptr)
	{
		delete jointBody_;
		jointBody_ = nullptr;
	}
}

void MotorJointComponent::SetDefaultProperties(const bool& flag)
{
	jointDef_->collideConnected = false;
	jointDef_->bodyA = owner_->body_;
	jointDef_->bodyB = target_->body_;
	jointDef_->correctionFactor = 0.5f;
	jointDef_->maxTorque = DefaultMotorMaxSpeed;
	jointDef_->maxTorque = DefaultMotorMaxSpeed;
	jointDef_->maxForce = DefaultMotorMaxSpeed;
	

	if (jointBody_ == nullptr)
	{
		jointBody_ = new MotorJoint(this, nullptr, flag);
	}
}

void MotorJointComponent::MotorJoint::CreateJoint(const bool& flag)
{
	if (flag)
		RESERVE(MotorJointComponent)


	else if (!flag)
	{
		if (joint_ != nullptr)
			DESTROY
			RESERVE(MotorJointComponent)
	}
}

void MotorJointComponent::MotorJoint::EnableCollision(const bool& flag)
{
	JOINT_DEF->collideConnected = flag;
	JOINT_RESETOR(MotorJointComponent)
}

void MotorJointComponent::MotorJoint::ConnectedRigidBody(Actor* target)
{
	JOINT_DEF->bodyB = target->body_;
	JOINT_RESETOR(MotorJointComponent)
		
}

void MotorJointComponent::MotorJoint::SetAngularOffset(const float& value)
{
	JOINT_DEF->angularOffset = value;
	if (joint_ != nullptr)
		joint_->SetAngularOffset(value);
	
}

void MotorJointComponent::MotorJoint::SetCorrectionFactor(const float& value)
{
	JOINT_DEF->correctionFactor = value;
	if (joint_ != nullptr)
		joint_->SetCorrectionFactor(value);
}

void MotorJointComponent::MotorJoint::SetLinearOffset(const Math::Vector2 pos)
{
	JOINT_DEF->linearOffset = b2Vec2(pos.x, pos.y);
	if (joint_ != nullptr)
		joint_->SetLinearOffset(JOINT_DEF->linearOffset);

	
}

void MotorJointComponent::MotorJoint::SetMaxForce(const float& value)
{
	JOINT_DEF->maxForce = value;
	if (joint_ != nullptr)
		joint_->SetMaxForce(value);
}

void MotorJointComponent::MotorJoint::SetMaxTorque(const float& value)
{
	JOINT_DEF->maxTorque = value;
	if (joint_ != nullptr)
		joint_->SetMaxTorque(value);
}

