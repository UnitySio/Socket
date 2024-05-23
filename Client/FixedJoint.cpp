#include "FixedJoint.h"
#include "../Engine/Actor/Actor.h"

void FixedJoint::EnableCollision(const bool& flag)
{
	jointDef_->collideConnected = flag;

	if (joint_ != nullptr)
		world_->DestroyJoint(joint_);
	joint_ = static_cast<b2DistanceJoint*>(world_->CreateJoint(jointDef_));
}

void FixedJoint::ConnectedRigidBody(Actor* target)
{
	if (jointDef_ == nullptr)
		jointDef_ = new b2DistanceJointDef;

	jointDef_->bodyB = target->body_;

	if (joint_ != nullptr)
		world_->DestroyJoint(joint_);
	joint_ = static_cast<b2DistanceJoint*>(world_->CreateJoint(jointDef_));
}

void FixedJoint::ConnectedAnchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorB = b2Vec2(pos.x, pos.y);
}

void FixedJoint::Anchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorA = b2Vec2(pos.x, pos.y);
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
