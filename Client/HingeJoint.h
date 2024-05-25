#pragma once
#include "BaseJoint.h"

class HingeJointComponent;

class HingeJoint : private BaseJoint<b2RevoluteJoint, b2RevoluteJointDef, HingeJointComponent>
{
public:
	HingeJoint(b2RevoluteJointDef* def);
	virtual ~HingeJoint() {};

	void EnableCollision(const bool& flag);
	void ConnectedRigidBody(Actor* target);
	void ConnectedAnchor(const Math::Vector2& pos);
	void Anchor(const Math::Vector2& pos);
	void AutoConfigureConnectedAnchor();
	void MotorSpeed(const float& value);



protected:
	void ResetJoint();
	
	

private:

	friend class HingeJointComponent;
};

