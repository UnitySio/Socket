#include "PrismaticJointComponent.h"
PrismaticJointComponent::PrismaticJointComponent(Actor* owner, const std::wstring& kName):
	Super(owner, kName),
	jointBody_(nullptr)
{
	owner_ = owner;
}


void PrismaticJointComponent::CreateJoint()
{
	auto temp = static_cast<b2PrismaticJoint*>(world_->CreateJoint(jointDef_));
	if (jointBody_ == nullptr)
		jointBody_ = new PrismaticJoint(this, temp);

	else
		jointBody_->joint_ = temp;
}

inline void PrismaticJointComponent::InitializeComponent()
{
	Super::InitializeComponent();

}

inline void PrismaticJointComponent::UninitializeComponent()
{
	Super::UninitializeComponent();

}

void PrismaticJointComponent::SetDefaultProperties(const bool& flag)
{
	jointDef_->bodyA = owner_->body_;
	jointDef_->bodyB = target_->body_;
	jointDef_->collideConnected = false;
	jointDef_->enableMotor = true;
	jointDef_->enableLimit = true;
	jointDef_->maxMotorForce = 1000.0f;
	jointDef_->motorSpeed = 10.0f;
	jointDef_->localAxisA = b2Vec2(1.0f, 1.0f);
	
	if (jointBody_ == nullptr)
	{
		jointBody_ = new PrismaticJoint(this, nullptr, flag);
	}

	
}



void PrismaticJointComponent::PrismaticJoint::CreateJoint(const bool& flag)
{
	if (flag)
		RESERVE(PrismaticJointComponent)


	else if (!flag)
	{
		if (joint_ != nullptr)
			DESTROY
			RESERVE(PrismaticJointComponent)
	}
}

void PrismaticJointComponent::PrismaticJoint::EnableCollision(const bool& flag)
{
	JOINT_DEF->collideConnected = flag;
	JOINT_RESETOR(PrismaticJointComponent)
}

void PrismaticJointComponent::PrismaticJoint::ConnectedRigidBody(Actor* target)
{
	JOINT_DEF->bodyB = target->body_;
	JOINT_RESETOR(PrismaticJointComponent)
}

void PrismaticJointComponent::PrismaticJoint::Anchor(const Math::Vector2& pos)
{
	JOINT_DEF->localAnchorA = b2Vec2(pos.x, pos.y);
	JOINT_RESETOR(PrismaticJointComponent)
}

void PrismaticJointComponent::PrismaticJoint::ConnectedAnchor(const Math::Vector2& pos)
{
	JOINT_DEF->localAnchorB = b2Vec2(pos.x, pos.y);
	JOINT_RESETOR(PrismaticJointComponent)

}

void PrismaticJointComponent::PrismaticJoint::SetMotorSpeed(const float& value)
{
	JOINT_DEF->motorSpeed = value;
	if(joint_ != nullptr)
		joint_->SetMotorSpeed(value);
}

void PrismaticJointComponent::PrismaticJoint::SetLimits(const float& lower, const float& upper)
{
	JOINT_DEF->lowerTranslation = lower;
	JOINT_DEF->upperTranslation = upper;
	if(joint_ != nullptr)
		joint_->SetLimits(lower, upper);
}

void PrismaticJointComponent::PrismaticJoint::SetMaxMotorForce(const float& value)
{
	JOINT_DEF->maxMotorForce = value;
	if(joint_ != nullptr)
		joint_->SetMaxMotorForce(value);
}
