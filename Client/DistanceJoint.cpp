#include "DistanceJoint.h"
#include "../Engine/Level/World.h"
#include "../Engine/Actor/Actor.h"
#include "../Client/Game/Map/MainMap.h"
#include "DistanceJointComponent.h"


DistanceJoint::DistanceJoint(b2DistanceJointDef* def):
	Super(def)
{
	
}

void DistanceJoint::EnableCollision(const bool& flag)
{
	jointDef_->collideConnected = flag;
	
	RESETOR(DistanceJoint)
}

void DistanceJoint::ConnectedRigidBody(Actor* target)
{
	jointDef_->bodyB = target->body_;
	RESETOR(DistanceJoint)
}

void DistanceJoint::ConnectedAnchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorB = b2Vec2(pos.x, pos.y);
	RESETOR(DistanceJoint)
}

void DistanceJoint::Anchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorA = b2Vec2(pos.x, pos.y);
	RESETOR(DistanceJoint)
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


void DistanceJoint::ResetJoint(b2Joint* joint, b2JointDef* jointDef, b2World* world)
{
	joint_ = static_cast<DistanceJoint*>(joint);
	jointDef_ = static_cast<b2DistanceJointDef*>(jointDef);
	world_ = world;
}

