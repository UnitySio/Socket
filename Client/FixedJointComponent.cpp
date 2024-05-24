#include "FixedJointComponent.h"
#include "../Engine/Actor/Actor.h"

FixedJointComponent::FixedJointComponent(Actor* owner, const std::wstring& kName):
	BaseJointComponent(owner, kName),
	owner_(owner)
{
}

inline void FixedJointComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

inline void FixedJointComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
}

void FixedJointComponent::SetDefaultProperties()
{
	jointDef_->bodyA = owner_->body_;
	jointDef_->bodyB = target_->body_;

	auto temp = static_cast<BaseJoint<b2DistanceJoint, b2DistanceJointDef, FixedJointComponent>*>(world_->CreateJoint(jointDef_));

	joint_ = (FixedJoint*)temp;

	joint_->SetJointDef(jointDef_);
}
