#include "FixedJoint.h"
#include "FixedJointComponent.h"
#include "../Engine/Level/World.h"

void FixedJoint::EnableCollision(const bool& flag)
{
	jointDef_->collideConnected = flag;
	RESETOR(FixedJoint)
}

void FixedJoint::ConnectedRigidBody(Actor* target)
{
	jointDef_->bodyB = target->body_;
	RESETOR(FixedJoint)
}

void FixedJoint::ConnectedAnchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorB = b2Vec2(pos.x, pos.y);
	RESETOR(FixedJoint)
}

void FixedJoint::Anchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorA = b2Vec2(pos.x, pos.y);
	RESETOR(FixedJoint)
}

void FixedJoint::Distance(const float& distance)
{
	jointDef_->length = distance;
	jointDef_->maxLength = distance;
	jointDef_->minLength = distance;

	if (joint_ != nullptr)
	{
		joint_->SetLength(distance);
		joint_->SetMinLength(distance);
		joint_->SetMaxLength(distance);
	}
}

void FixedJoint::ResetJoint()
{
	joint_ = (b2DistanceJoint*)world_->CreateJoint(static_cast<b2DistanceJointDef*>(jointDef_));
	
	
}
