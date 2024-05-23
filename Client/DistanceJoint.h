#pragma once
#include "BaseJoint.h"
#include "box2d/box2d.h"

class DistanceJoint : public BaseJoint<b2DistanceJoint, b2DistanceJointDef>
{
public:
	DistanceJoint(const b2DistanceJointDef* def) :
		BaseJoint(def)
	{};
	virtual ~DistanceJoint() {};




};

