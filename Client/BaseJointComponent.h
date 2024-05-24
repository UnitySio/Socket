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
		world_(World::Get()->physics_world_.get())
	{};
	virtual ~BaseJointComponent() {};



	T* GetJoint() { return joint_; }
	U* GetJointDef() { return jointDef_; }
	void SetJointDef(U* input) { jointDef_ = input; }


	void CreateJointDefWithTarget(Actor* target);
	virtual void CreateJoint() = 0;
protected:
	using Super = BaseJointComponent;

	virtual void SetDefaultProperties() = 0;


	T* joint_;
	U* jointDef_;
	Actor* owner_;
	Actor* target_;
	b2World* world_;
};

template<typename T, typename U>
inline void BaseJointComponent<T, U>::CreateJointDefWithTarget(Actor* target)
{
	if(jointDef_ == nullptr)
		jointDef_ = new U;
	target_ = target;
	SetDefaultProperties();
}



#define RESETOR(_JointType) if (joint_ != nullptr)\
static_cast<MainMap*>(World::Get()->GetLevel())->ReserveDestroyJoint(joint_);\
static_cast<MainMap*>(World::Get()->GetLevel())->ReserveCreateJoint(joint_, jointDef_, std::bind(&_JointType::ResetJoint, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
