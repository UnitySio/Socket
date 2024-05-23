#include "DistanceJointComponent.h"
#include "box2d/box2d.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include <memory>
#include "Actor/Actor.h"
#include "../Engine/Level/World.h"
#include "BaseJoint.h"


DistanceJointComponent::DistanceJointComponent(Actor* owner, const std::wstring& kName) :
	BaseJointComponent(owner, kName),
	owner_(owner)
{
}

inline void DistanceJointComponent::InitializeComponent()
{
	ActorComponent::InitializeComponent();
	
}

inline void DistanceJointComponent::UninitializeComponent()
{
	ActorComponent::UninitializeComponent();
	delete joint_->GetJoint();
	
	if (joint_ != nullptr)
	{
		world_->DestroyJoint(joint_->GetJoint());
		delete joint_;
		joint_ = nullptr;
	}
}

void DistanceJointComponent::SetDefaultProperties()
{
	jointDef_->collideConnected = false;
	jointDef_->maxLength = 3.0f;
	jointDef_->bodyA = owner_->body_;
	jointDef_->bodyB = target_->body_;
	


	auto temp = static_cast<BaseJoint<b2DistanceJoint, b2DistanceJointDef, DistanceJointComponent>*>(world_->CreateJoint(jointDef_));
	
	
	
	joint_ = (DistanceJoint*)(temp);


	joint_->SetJoint((b2DistanceJoint*)joint_);
	joint_->SetJointDef(jointDef_);
	
	//temp->SetJointComponent(this);
}

