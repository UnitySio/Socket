#include "HingeJointComponent.h"
#include "HingeJoint.h"
HingeJointComponent::HingeJointComponent(class Actor* owner, const std::wstring& kName):
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

void HingeJointComponent::SetDefaultProperties()
{
	jointDef_->collideConnected = false;
	jointDef_->bodyA = owner_->body_;
	jointDef_->bodyB = target_->body_;
	jointDef_->enableLimit = false;
	jointDef_->enableMotor = true;
	
	
}

void HingeJointComponent::CreateJoint()
{
	auto temp = static_cast<BaseJoint<b2RevoluteJoint, b2DistanceJointDef, HingeJointComponent>*>(world_->CreateJoint(jointDef_));

	joint_ = (HingeJoint*)(temp);
	joint_->SetJoint((b2RevoluteJoint*)joint_);
	joint_->SetJointDef(jointDef_);
}
