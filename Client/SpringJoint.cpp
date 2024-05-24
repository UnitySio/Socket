#include "SpringJoint.h"
#include "../Engine/Actor/Actor.h"
#include "SpringJointComponent.h"
SpringJoint::SpringJoint(b2DistanceJointDef* def):
	Super(def)
{
	
}

void SpringJoint::EnableCollision(const bool& flag)
{
}

void SpringJoint::ConnectedRigidBody(Actor* target)
{
	jointDef_->bodyB = target->body_;
	RESETOR(SpringJoint)
}

void SpringJoint::ConnectedAnchor(const Math::Vector2& pos)
{
}

void SpringJoint::Anchor(const Math::Vector2& pos)
{
}

void SpringJoint::AutoConfigureConnectedAnchor()
{
}



void SpringJoint::ResetJoint(b2Joint* joint, b2JointDef* jointDef, b2World* world)
{
	joint_ = static_cast<SpringJoint*>(joint);
	jointDef_ = static_cast<b2DistanceJointDef*>(jointDef);
	world_ = world;
}
