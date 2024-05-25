#pragma once
#include "../Engine/Actor/Component/ActorComponent.h"
#include "../Engine/Actor/Actor.h"
#include "../Engine/Level/World.h"
#include "box2d.h"
#include "../Client/Game/Map/MainMap.h"
#include <type_traits>

template<typename T, typename U>
class BaseJointComponent : public ActorComponent, public b2JointUserData
{
public:
	BaseJointComponent(class Actor* owner, const std::wstring& kName) :
		ActorComponent(owner, kName),
		joint_(nullptr),
		jointDef_(nullptr),
		owner_(owner),
		target_(nullptr),
		world_(World::Get()->physics_world_.get()),
		origin_(nullptr)
	{}
	virtual ~BaseJointComponent() {}
	void CreateJointDefWithTarget(Actor* target);
	virtual void CreateJoint() abstract;

protected:
	using Super = BaseJointComponent;
	virtual void SetDefaultProperties() abstract;

	b2Joint* origin_;
	T* joint_;
	U* jointDef_;
	Actor* owner_;
	Actor* target_;
	b2World* world_;
};



template<typename T, typename U>
inline void BaseJointComponent<T, U>::CreateJointDefWithTarget(Actor* target)
{
	if (jointDef_ == nullptr)
		jointDef_ = new U;
	target_ = target;
	SetDefaultProperties();
}


