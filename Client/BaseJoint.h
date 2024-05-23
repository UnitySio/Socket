#pragma once
#include "box2d/box2d.h"
#include "../Engine/Level/World.h"
#include <type_traits>

template<typename T, typename U>
class BaseJoint : public T
{
public:
	BaseJoint(U* def) :
		T(def),
		joint_(nullptr),
		jointDef_(def),
		world_(World::Get()->physics_world_.get())
	{};
	virtual ~BaseJoint() 
	{
		delete jointDef_;
		delete joint_;
	};

	void SetJoint(T* input) { joint_ = input; }
	void SetJointDef(U* input) { jointDef_ = input; }
	T* GetJoint() { return joint_; }
	const U* GetJointDef() { return jointDef_; }

protected:
	T* joint_;
	U* jointDef_;
	b2World* world_;

private:
	template<typename Ty, typename Fy>
	friend class BaseJointComponent;
};

