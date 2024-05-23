#pragma once
#include "../Engine/Actor/Component/ActorComponent.h"
#include "../Engine/Actor/Actor.h"
#include "../Engine/Level/World.h"
#include "box2d.h"
#include <type_traits>

template<typename T, typename U>
class BaseJointComponent : public ActorComponent, public b2JointUserData
{
	using Super = ActorComponent;
public:
	BaseJointComponent(class Actor* owner, const std::wstring& kName) :
		ActorComponent(owner, kName),
		joint_(nullptr),
		jointDef_(nullptr),
		owner_(owner),
		target_(nullptr),
		world_(World::Get()->physics_world_.get())
	{};
	virtual ~BaseJointComponent() {};



	T* GetJoint() { return joint_; }
	U* GetJointDef() { return jointDef_; }
	void SetJointDef(U* input) { jointDef_ = input; }


	void CreateJointDef(Actor* target);

protected:
	virtual void SetDefaultProperties() = 0;


	T* joint_;
	U* jointDef_;
	Actor* owner_;
	Actor* target_;
	b2World* world_;
};

template<typename T, typename U>
inline void BaseJointComponent<T, U>::CreateJointDef(Actor* target)
{
	if(jointDef_ == nullptr)
		jointDef_ = new U;
	target_ = target;
	
	SetDefaultProperties();
	
}


constexpr uintptr_t DistanceJointComponent_Pointer = 1;