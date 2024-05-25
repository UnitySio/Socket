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
	jointDef_->collideConnected = false;
	jointDef_->length = 2.0f;
	jointDef_->maxLength = 2.0f;
	jointDef_->minLength = 2.0f;
	jointDef_->damping = 1.0f;
}

void FixedJointComponent::CreateJoint()
{
	origin_ = world_->CreateJoint(jointDef_);
	auto temp = static_cast<BaseJoint<b2DistanceJoint, b2DistanceJointDef, FixedJointComponent>*>(origin_);
	
	joint_ = static_cast<FixedJoint*>(temp);
	joint_->SetJointDef(jointDef_);
	joint_->SetJoint(static_cast<b2DistanceJoint*>(origin_));
	joint_->jointComponent_ = this;
	joint_->world_ = world_;
}
