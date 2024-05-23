#include "DistanceJointComponent.h"
#include "box2d/box2d.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include <memory>
#include "Actor/Actor.h"
#include "../Engine/Level/World.h"


DistanceJointComponent::DistanceJointComponent(Actor* owner, const std::wstring& kName) :
	BaseJointComponent(owner, kName),
	owner_(owner),
	world_(World::Get()->physics_world_.get())
{
	joint_ = new DistanceJoint(new b2DistanceJointDef);
	jointDef_ = joint_->GetJointDef();
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

void DistanceJointComponent::EnableCollision(const bool& flag)
{
	jointDef_->collideConnected = flag;

	if (joint_ != nullptr)
		world_->DestroyJoint(joint_);
	joint_->SetJoint(static_cast<b2DistanceJoint*>(world_->CreateJoint(jointDef_)));
}

void DistanceJointComponent::ConnectedRigidBody(Actor* target)
{
	jointDef_->bodyB = target->body_;

	if(joint_ != nullptr)
		world_->DestroyJoint(joint_);
	joint_->SetJoint(static_cast<b2DistanceJoint*>(world_->CreateJoint(jointDef_)));
}

void DistanceJointComponent::ConnectedAnchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorB = b2Vec2(pos.x, pos.y);
}

void DistanceJointComponent::Anchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorA = b2Vec2(pos.x, pos.y);
}

void DistanceJointComponent::AutoConfigureConnectedAnchor()
{
	jointDef_->localAnchorA = b2Vec2_zero;
	jointDef_->localAnchorB = b2Vec2_zero;
}

void DistanceJointComponent::Distance(const float& distance)
{
	jointDef_->length = distance;
	if(joint_ != nullptr)
		joint_->SetLength(distance);
}

void DistanceJointComponent::MaxDistanceOnly(const bool& flag)
{
	jointDef_->length = jointDef_->maxLength;
	if (joint_ != nullptr)
		joint_->SetLength(joint_->GetMaxLength());
}

void DistanceJointComponent::SetMaxDistance(const float& distance)
{
	jointDef_->maxLength = distance;
	if (joint_ != nullptr)
		joint_->SetMaxLength(distance);
}

void DistanceJointComponent::SetMinDistance(const float& distance)
{
	jointDef_->minLength = distance;
	if (joint_ != nullptr)
		joint_->SetMinLength(distance);
}

void DistanceJointComponent::SetDampingValue(const float& value)
{
	jointDef_->damping = value;
	if (joint_ != nullptr)
		joint_->SetDamping(value);
}

void DistanceJointComponent::SetStiffness(const float& value)
{
	jointDef_->stiffness = value;
	if (joint_ != nullptr)
		joint_->SetStiffness(value);
}

