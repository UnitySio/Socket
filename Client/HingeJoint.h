#pragma once
#include "BaseJoint.h"

class HingeJointComponent;

class HingeJoint : public BaseJoint<b2RevoluteJoint, b2RevoluteJointDef, HingeJointComponent>
{
	using Super = BaseJoint;
public:
	HingeJoint(b2RevoluteJointDef* def);
	virtual ~HingeJoint() {};







protected:
	void ResetJoint(b2Joint* joint, b2JointDef* jointDef, b2World* world);
	
	b2JointUserData& GetUserData() { return joint_->GetUserData(); };


	b2RevoluteJoint* GetJoint() { return joint_; }
	const b2RevoluteJointDef* GetJointDef() { return jointDef_; }
	void SetJoint(b2RevoluteJoint* input) { joint_ = input; }
	void SetJointDef(b2RevoluteJointDef* input) { jointDef_ = input; }

private:


};

