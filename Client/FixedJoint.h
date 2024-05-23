#pragma once
#include "BaseJoint.h"
#include "../Engine/Math/Vector2.h"
class Actor;
class FixedJointComponent;

class FixedJoint : private BaseJoint<b2DistanceJoint, b2DistanceJointDef, FixedJointComponent>
{
public:
	FixedJoint(b2DistanceJointDef* def) :
		BaseJoint(def)
	{};
	virtual ~FixedJoint() {};

	void EnableCollision(const bool& flag);
	void ConnectedRigidBody(Actor* target);
	void ConnectedAnchor(const Math::Vector2& pos);
	void Anchor(const Math::Vector2& pos);
	void Distance(const float& distance);


	b2DistanceJoint* GetJoint() { return joint_; }
	const b2DistanceJointDef* GetJointDef() { return jointDef_; }

private:
	template<typename Ty, typename Fy>
	friend class BaseJointComponent;
};

