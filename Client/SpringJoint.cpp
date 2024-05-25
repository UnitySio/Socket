#include "SpringJoint.h"
#include "../Engine/Actor/Actor.h"
#include "SpringJointComponent.h"
SpringJoint::SpringJoint(b2DistanceJointDef* def):
	Super(def)
{
	
}

void SpringJoint::EnableCollision(const bool& flag)
{
	jointDef_->collideConnected = flag;
	RESETOR(SpringJoint)
}

void SpringJoint::ConnectedRigidBody(Actor* target)
{
	jointDef_->bodyB = target->body_;
	RESETOR(SpringJoint)
}

void SpringJoint::ConnectedAnchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorA = b2Vec2(pos.x, pos.y);
	RESETOR(SpringJoint)
}

void SpringJoint::Anchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorB = b2Vec2(pos.x, pos.y);
	RESETOR(SpringJoint)
}

void SpringJoint::AutoConfigureConnectedAnchor()
{

}

void SpringJoint::SetDistance(const float& value)
{
	jointDef_->length = value;
	joint_->SetLength(value);
}

void SpringJoint::SetDampingRatio(const float& value)
{
	jointDef_->damping = value;
	joint_->SetDamping(value);
}

void SpringJoint::SetFrequency(const float& value)
{
	jointDef_->stiffness = value;
	joint_->SetStiffness(value);
	
}

void SpringJoint::SetMaxDistance(const float& value)
{
	if (jointDef_->length > jointDef_->maxLength)
	{
		jointDef_->length = value;
		joint_->SetLength(value);
	}
	jointDef_->maxLength = value;
	joint_->SetMaxLength(value);
}

void SpringJoint::SetMinDistance(const float& value)
{
	jointDef_->minLength = value;
	joint_->SetMinLength(value);
}



void SpringJoint::ResetJoint()
{
	joint_ = static_cast<b2DistanceJoint*>(world_->CreateJoint(jointDef_));
}
