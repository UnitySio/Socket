#include "WheelJointComponent.h"

WheelJointComponent::WheelJointComponent(Actor* owner, const std::wstring& kName):
	Super(owner, kName),
	jointBody_(nullptr)
{
	owner_ = owner;
}

void WheelJointComponent::CreateJoint()
{
	auto temp = static_cast<b2WheelJoint*>(world_->CreateJoint(jointDef_));
	if (jointBody_ == nullptr)
		jointBody_ = new WheelJoint(this, temp);

	else
		jointBody_->joint_ = temp;
}

inline void WheelJointComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

inline void WheelJointComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
	if (jointBody_ != nullptr)
	{
		delete jointBody_;
		jointBody_ = nullptr;
	}
}

void WheelJointComponent::SetDefaultProperties(const bool& flag)
{
	jointDef_->collideConnected = false;
	jointDef_->bodyA = owner_->body_;
	jointDef_->bodyB = target_->body_;
	jointDef_->enableLimit = true;
	jointDef_->enableMotor = true;
	jointDef_->maxMotorTorque = DefaultMotorMaxSpeed;

	if (jointBody_ == nullptr)
	{
		jointBody_ = new WheelJoint(this, nullptr, flag);
	}
}

void WheelJointComponent::WheelJoint::CreateJoint(const bool& flag)
{
	if (flag)
		RESERVE(WheelJointComponent)


	else if (!flag)
	{
		if (joint_ != nullptr)
			DESTROY
			RESERVE(WheelJointComponent)
	}
}

void WheelJointComponent::WheelJoint::EnableCollision(const bool& flag)
{
	JOINT_DEF->collideConnected = flag;
	JOINT_RESETOR(WheelJointComponent)
}

void WheelJointComponent::WheelJoint::ConnectedRigidBody(Actor* target)
{
	JOINT_DEF->bodyB = target->body_;
	JOINT_RESETOR(WheelJointComponent)
}

void WheelJointComponent::WheelJoint::Anchor(const Math::Vector2& pos)
{
	JOINT_DEF->localAnchorA = b2Vec2(pos.x, pos.y);
	JOINT_RESETOR(WheelJointComponent)
}

void WheelJointComponent::WheelJoint::ConnectedAnchor(const Math::Vector2& pos)
{
	JOINT_DEF->localAnchorB = b2Vec2(pos.x, pos.y);
	JOINT_RESETOR(WheelJointComponent)
}

void WheelJointComponent::WheelJoint::SetDamping(const float& value)
{
	JOINT_DEF->damping = value;
	if (joint_ != nullptr)
		joint_->SetDamping(value);
}

void WheelJointComponent::WheelJoint::SetLimits(const float& lower, const float& upper)
{
	JOINT_DEF->lowerTranslation = lower;
	JOINT_DEF->upperTranslation = upper;
	if(joint_ != nullptr)
		joint_->SetLimits(lower, upper);
}

void WheelJointComponent::WheelJoint::SetMaxMortorTorque(const float& value)
{
	JOINT_DEF->maxMotorTorque = value;
	if (joint_ != nullptr)
		joint_->SetMaxMotorTorque(value);
}

void WheelJointComponent::WheelJoint::SetMotorSpeed(const float& value)
{
	JOINT_DEF->motorSpeed = value;
	if (joint_ != nullptr)
		joint_->SetMotorSpeed(value);
}

void WheelJointComponent::WheelJoint::SetStiffness(const float& value)
{
	JOINT_DEF->stiffness = value;
	if (joint_ != nullptr)
		joint_->SetStiffness(value);
}
