#pragma once
#include "box2d/box2d.h"
#include "../Engine/Level/World.h"
#include <type_traits>
#include "../Engine/Math/Vector2.h"


class Actor;

template<typename T, typename U, typename V>
class BaseJoint : public T
{
public:
	BaseJoint(U* def) :
		T(def),
		joint_(nullptr),
		jointDef_(def),
		jointComponent_(nullptr),
		world_(World::Get()->physics_world_.get())
	{};
	virtual ~BaseJoint() 
	{
		delete jointDef_;
		world_->DestroyJoint(joint_);
	};
	
	



	void SetJointComponent(V* jointComp) { jointComponent_ = jointComp; };
	V* GetJointComponent() { return jointComponent_; };


	
	b2JointUserData& GetUserData() { return joint_->GetUserData(); };

	T* GetJoint() { return joint_; }
	const U* GetJointDef() { return jointDef_; }
	void SetJoint(T* input) 
	{ 
		joint_ = input; 
	}
	void SetJointDef(U* input) { jointDef_ = input; }
	


protected:
	using Super = BaseJoint;
	T* joint_;
	U* jointDef_;
	b2World* world_;
	V* jointComponent_;

private:
	template<typename Ty, typename Fy>
	friend class BaseJointComponent;
	friend class DistanceJointComponent;
	friend class DistanceJoint;
};

