#include "HingeJoint.h"

HingeJoint::HingeJoint(b2RevoluteJointDef* def):
	BaseJoint(def)
{
}






void HingeJoint::ResetJoint(b2Joint* joint, b2JointDef* jointDef, b2World* world)
{
	joint_ = static_cast<HingeJoint*>(joint);
	jointDef_ = static_cast<b2RevoluteJointDef*>(jointDef);
	world_ = world;
}
