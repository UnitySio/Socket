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
	void SetDistance(const float& value);
	void SetDampingRatio(const float& value);
	void SetFrequency(const float& value);
	void SetMaxDistance(const float& value);
	void SetMinDistance(const float& value);



protected:
	void ResetJoint();







private:
	friend class SpringJointComponent;
};

