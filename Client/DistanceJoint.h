#pragma once
#include "BaseJoint.h"
#include "box2d/box2d.h"
#include "../Engine/Math/Vector2.h"

class Actor;


class DistanceJoint : public BaseJoint<b2DistanceJoint, b2DistanceJointDef>
{
public:
	DistanceJoint(b2DistanceJointDef* def) :
		BaseJoint(def)
	{
		jointDef_ = def;
	};
	virtual ~DistanceJoint() {};

	void EnableCollision(const bool& flag);
	void ConnectedRigidBody(Actor* target);
	void ConnectedAnchor(const Math::Vector2& pos);
	void Anchor(const Math::Vector2& pos);
	void AutoConfigureConnectedAnchor();
	void Distance(const float& distance);
	void MaxDistanceOnly(const bool& flag);
	void SetMaxDistance(const float& distance);
	void SetMinDistance(const float& distance);
	void SetDampingValue(const float& value);
	void SetStiffness(const float& value);


};

