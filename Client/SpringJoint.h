#pragma once
#include "BaseJoint.h"

class SpringJointComponent;

class SpringJoint : private BaseJoint<b2DistanceJoint, b2DistanceJointDef, SpringJointComponent>
{
public:
	SpringJoint(b2DistanceJointDef* def);
	virtual ~SpringJoint() {};

	void EnableCollision(const bool& flag);
	void ConnectedRigidBody(Actor* target);
	void ConnectedAnchor(const Math::Vector2& pos);
	void Anchor(const Math::Vector2& pos);
	void AutoConfigureConnectedAnchor();


protected:
	void ResetJoint(b2Joint* joint, b2JointDef* jointDef, b2World* world);







private:
	friend class SpringJointComponent;
};

