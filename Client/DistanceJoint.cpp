#include "DistanceJoint.h"
#include "../Engine/Level/World.h"
#include "../Engine/Actor/Actor.h"

void DistanceJoint::EnableCollision(const bool& flag)
{
	jointDef_->collideConnected = flag;

	if (joint_ != nullptr)
		world_->DestroyJoint(joint_);
	joint_ = static_cast<b2DistanceJoint*>(world_->CreateJoint(jointDef_));
}

void DistanceJoint::ConnectedRigidBody(Actor* target)
{
	if (jointDef_ == nullptr)
		jointDef_ = new b2DistanceJointDef;

	jointDef_->bodyB = target->body_;

	if (joint_ != nullptr)
		world_->DestroyJoint(joint_);
	joint_ = static_cast<b2DistanceJoint*>(world_->CreateJoint(jointDef_));
}

void DistanceJoint::ConnectedAnchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorB = b2Vec2(pos.x, pos.y);
}

void DistanceJoint::Anchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorA = b2Vec2(pos.x, pos.y);
}

void DistanceJoint::AutoConfigureConnectedAnchor()
{
	jointDef_->localAnchorA = b2Vec2_zero;
	jointDef_->localAnchorB = b2Vec2_zero;
}

void DistanceJoint::Distance(const float& distance)
{
	jointDef_->length = distance;
	if (joint_ != nullptr)
		joint_->SetLength(distance);
}

void DistanceJoint::MaxDistanceOnly(const bool& flag)
{
	jointDef_->length = jointDef_->maxLength;
	if (joint_ != nullptr)
		joint_->SetLength(joint_->GetMaxLength());
}

void DistanceJoint::SetMaxDistance(const float& distance)
{
	jointDef_->maxLength = distance;
	if (joint_ != nullptr)
		joint_->SetMaxLength(distance);
}

void DistanceJoint::SetMinDistance(const float& distance)
{
	jointDef_->minLength = distance;
	if (joint_ != nullptr)
		joint_->SetMinLength(distance);
}

void DistanceJoint::SetDampingValue(const float& value)
{
	jointDef_->damping = value;
	if (joint_ != nullptr)
		joint_->SetDamping(value);
}

void DistanceJoint::SetStiffness(const float& value)
{
	jointDef_->stiffness = value;
	if (joint_ != nullptr)
		joint_->SetStiffness(value);
}

