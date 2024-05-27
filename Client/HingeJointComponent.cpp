#include "HingeJointComponent.h"

HingeJointComponent::HingeJointComponent(Actor* owner, const std::wstring& kName):
	Super(owner, kName), 
	jointBody_(nullptr)
{
	owner_ = owner;
}

inline void HingeJointComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

inline void HingeJointComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
	if (jointBody_ != nullptr)
	{
		delete jointBody_;
		jointBody_ = nullptr;
	}
}

void HingeJointComponent::SetDefaultProperties(const bool& flag)
{
	jointDef_->bodyA = owner_->body_;
	jointDef_->bodyB = target_->body_;
	jointDef_->collideConnected = false;
	jointDef_->enableLimit = false;
	jointDef_->enableMotor = true;
	jointDef_->maxMotorTorque = 1000.0f;
	
	if (jointBody_ == nullptr)
	{
		jointBody_ = new HingeJoint(this, nullptr, flag);
	}
}

void HingeJointComponent::CreateJoint()
{
	auto temp = static_cast<b2RevoluteJoint*>(world_->CreateJoint(jointDef_));
	if (jointBody_ == nullptr)
		jointBody_ = new HingeJoint(this, temp);

	else
		jointBody_->joint_ = temp;
}

void HingeJointComponent::HingeJoint::CreateJoint(const bool& flag)
{
	if (flag)
	{
	}
		


	else if (!flag)
	{
		if (joint_ != nullptr)
			DESTROY
		RESERVE(HingeJointComponent)
	}
}

void HingeJointComponent::HingeJoint::EnableCollision(const bool& flag)
{
	JOINT_DEF->collideConnected = flag;
	JOINT_RESETOR(HingeJointComponent)
}

void HingeJointComponent::HingeJoint::ConnectedRigidBody(Actor* target)
{
	JOINT_DEF->bodyB = target->body_;
	JOINT_RESETOR(HingeJointComponent)
}

void HingeJointComponent::HingeJoint::Anchor(const Math::Vector2& pos)
{
	JOINT_DEF->localAnchorA = b2Vec2(pos.x, pos.y);
	JOINT_RESETOR(HingeJointComponent)
}

void HingeJointComponent::HingeJoint::ConnectedAnchor(const Math::Vector2& pos)
{
	JOINT_DEF->localAnchorB = b2Vec2(pos.x, pos.y);
	JOINT_RESETOR(HingeJointComponent)

}

void HingeJointComponent::HingeJoint::SetUseMotor(const bool& flag)
{
	JOINT_DEF->enableMotor = flag;
	joint_->EnableMotor(flag);
}

void HingeJointComponent::HingeJoint::SetMotorSpeed(const float& value)
{
	JOINT_DEF->motorSpeed = value;
	joint_->SetMotorSpeed(value);
}

void HingeJointComponent::HingeJoint::SetMaxTorque(const float& value)
{
	JOINT_DEF->maxMotorTorque = value;
	joint_->SetMaxMotorTorque(value);
}

void HingeJointComponent::HingeJoint::SetLimitsEnabled(const bool& flag)
{
	JOINT_DEF->enableLimit = flag;
	joint_->EnableLimit(flag);
}

void HingeJointComponent::HingeJoint::SetLimitLowerUpper(const float& lower, const float& upper)
{
	JOINT_DEF->lowerAngle = lower;
	JOINT_DEF->upperAngle = upper;
	joint_->SetLimits(lower, upper);
}
