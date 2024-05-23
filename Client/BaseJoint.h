#pragma once
#include "box2d/box2d.h"
#include <type_traits>

template<typename T, typename U>
class BaseJoint : public T
{
public:
	BaseJoint(const U* def) :
		T(def)
	{};
	virtual ~BaseJoint() {};

	void SetJoint(T* input) { joint_ = input; }
	void SetJointDef(U* input) { jointDef_ = input; }
	T* GetJoint() { return joint_; }
	U* GetJointDef() { return jointDef_; }

private:
	T* joint_;
	U* jointDef_;

};

