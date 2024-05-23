#include "DistanceJointComponent.h"
#include "box2d/box2d.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include <memory>
#include "Actor/Actor.h"
#include "../Engine/Level/World.h"


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

