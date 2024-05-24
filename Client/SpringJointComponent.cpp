#include "SpringJointComponent.h"
#include "../Engine/Actor/Actor.h"
#include "BaseJoint.h"

SpringJointComponent::SpringJointComponent(Actor* owner, const std::wstring& kName) :
	Super(owner, kName)
{
	owner_ = owner;
}

void SpringJointComponent::SetDefaultProperties()
{
	jointDef_->bodyA = owner_->body_;
	jointDef_->bodyB = target_->body_;
	jointDef_->collideConnected = false;
	jointDef_->minLength = 0.0f;
	jointDef_->maxLength = 2.5f;
	jointDef_->length = 1.5f;
	jointDef_->stiffness = 250.0f;
	jointDef_->damping = 0.1f;
	
}

void SpringJointComponent::CreateJoint()
{
	joint_ = (SpringJoint*)world_->CreateJoint(static_cast<b2DistanceJointDef*>(jointDef_));
	joint_->SetJoint((b2DistanceJoint*)joint_);
	joint_->SetJointDef(jointDef_);
	joint_->world_ = world_;
	joint_->jointComponent_ = this;

}
