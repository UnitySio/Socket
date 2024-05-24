#include "HingeJoint.h"
#include "../Engine/Actor/Actor.h"
#include "HingeJointComponent.h"
HingeJoint::HingeJoint(b2RevoluteJointDef* def):
	BaseJoint(def)
{

}

void HingeJoint::EnableCollision(const bool& flag)
{
	jointDef_->collideConnected = flag;
	RESETOR(HingeJoint)
}

void HingeJoint::ConnectedRigidBody(Actor* target)
{
	jointDef_->bodyB = target->body_;
	RESETOR(HingeJoint)
}

void HingeJoint::ConnectedAnchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorA = b2Vec2(pos.x, pos.y);
	RESETOR(HingeJoint)
}

void HingeJoint::Anchor(const Math::Vector2& pos)
{
	jointDef_->localAnchorB = b2Vec2(pos.x, pos.y);
	RESETOR(HingeJoint)
}

void HingeJoint::AutoConfigureConnectedAnchor()
{
	
}

void HingeJoint::MotorSpeed(const float& value)
{
	jointDef_->motorSpeed = value;
	joint_->SetMotorSpeed(value);
}






void HingeJoint::ResetJoint(b2Joint* joint, b2JointDef* jointDef, b2World* world)
{
	joint_ = static_cast<HingeJoint*>(joint);
	jointDef_ = static_cast<b2RevoluteJointDef*>(jointDef);
	world_ = world;
}
