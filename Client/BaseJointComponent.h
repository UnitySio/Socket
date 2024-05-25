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
		jointDef_(nullptr),
		owner_(owner),
		target_(nullptr),
		world_(World::Get()->physics_world_.get())
	{}
	virtual ~BaseJointComponent() {}
	void CreateJointDefWithTarget(Actor* target, const bool& flag = false);

protected:
	using Super = BaseJointComponent;
	virtual void CreateJoint() abstract;
	virtual void SetDefaultProperties() abstract;

	U* jointDef_;
	Actor* owner_;
	Actor* target_;
	b2World* world_;
};



template<typename T, typename U>
inline void BaseJointComponent<T, U>::CreateJointDefWithTarget(Actor* target, const bool& flag)
{
	if (jointDef_ == nullptr)
		jointDef_ = new U;
	target_ = target;
	SetDefaultProperties();

	if (flag)
		CreateJoint();
	
		
}




#define JOINT_RESETOR(_JointComponentType) static_cast<MainMap*>(World::Get()->GetLevel())->ReserveDestroyJoint(joint_);\
static_cast<MainMap*>(World::Get()->GetLevel())->ReserveCreateJoint(std::bind(&_JointComponentType::CreateJoint, this->component_));

#define JOINT_DEF component_->jointDef_