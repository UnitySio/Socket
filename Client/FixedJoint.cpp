#include "FixedJoint.h"
#include "FixedJointComponent.h"
#include "../Engine/Level/World.h"

void FixedJoint::EnableCollision(const bool& flag)
{
	jointDef_->collideConnected = flag;

	
}

void FixedJoint::ConnectedRigidBody(Actor* target)
{
	if (jointDef_ == nullptr)
		jointDef_ = new b2DistanceJointDef;

	jointDef_->bodyB = target->body_;

	
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

void FixedJoint::ResetJoint(b2Joint* joint, b2JointDef* jointDef, b2World* world)
{

}
