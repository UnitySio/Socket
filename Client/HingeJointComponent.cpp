#include "HingeJointComponent.h"

HingeJointComponent::HingeJointComponent(Actor* owner, const std::wstring& kName):
	Super(owner, kName)
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

}

void HingeJointComponent::SetDefaultProperties(const bool& flag)
{
	jointDef_->bodyA = owner_->body_;
	jointDef_->bodyB = target_->body_;
	jointDef_->collideConnected = false;
	jointDef_->enableLimit = false;
	jointDef_->enableMotor = true;
	jointDef_->maxMotorTorque = 1000.0f;
}

void HingeJointComponent::CreateJoint()
{

}