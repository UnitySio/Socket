#include "DistanceJointComponent.h"
#include "box2d/box2d.h"
#include "../Engine/Actor/Component/RigidBodyComponent.h"
#include <memory>
#include "Actor/Actor.h"
#include "../Engine/Level/World.h"

DistanceJointComponent::DistanceJointComponent(Actor* owner, const std::wstring& kName) :
	ActorComponent(owner, kName),
	jointDef_(new b2DistanceJointDef),
	owner_(owner),
	joint_(nullptr),
	world_(World::Get()->physics_world_.get())
{
	jointDef_->bodyA = owner_->body_;
}

inline void DistanceJointComponent::InitializeComponent()
{
	ActorComponent::InitializeComponent();
	jointDef_->bodyA = owner_->body_;
	if (jointDef_->bodyB != nullptr)
		joint_ = static_cast<b2DistanceJoint*>(world_->CreateJoint(jointDef_));
}

inline void DistanceJointComponent::UninitializeComponent()
{
	ActorComponent::UninitializeComponent();
	delete jointDef_;
	if (joint_ != nullptr)
	{
		world_->DestroyJoint(joint_);
		joint_ = nullptr;
	}
}

void DistanceJointComponent::EnableCollision(const bool& flag)
{
	jointDef_->collideConnected = flag;

	if (joint_ != nullptr)
		world_->DestroyJoint(joint_);
	joint_ = static_cast<b2DistanceJoint*>(world_->CreateJoint(jointDef_));
}

void DistanceJointComponent::ConnectedRigidBody(Actor* target)
{
	jointDef_->bodyB = target->body_;

	if(joint_ != nullptr)
		world_->DestroyJoint(joint_);
	joint_ = static_cast<b2DistanceJoint*>(world_->CreateJoint(jointDef_));
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

