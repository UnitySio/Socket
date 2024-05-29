#pragma once
#include "../Engine/Math/Vector2.h"
#include "../Engine/Actor/Component/ActorComponent.h"
#include "../Engine/Actor/Actor.h"
#include "../Engine/Level/World.h"
#include "box2d.h"
#include "../Client/Game/Map/MainMap.h"
#include <type_traits>

#define OPT_JOINT_RESET
//#define OPT_JOINT_NONRESET

#if !defined(OPT_JOINT_RESET) && !defined(OPT_JOINT_NONRESET)
#define OPT_JOINT_RESET
#endif

template<typename T, typename U>
class BaseJointComponent : public ActorComponent, public b2JointUserData
{
	static_assert(std::is_base_of<b2Joint, T>::value, "T must be derived from b2Joint");
	static_assert(std::is_base_of<b2JointDef, U>::value, "U must be derived from b2JointDef");
public:
	BaseJointComponent(class Actor* owner, const std::wstring& kName) :
		ActorComponent(owner, kName),
		jointDef_(nullptr),
		owner_(owner),
		target_(nullptr),
		world_(World::Get()->physics_world_.get())
	{}
	virtual ~BaseJointComponent() {}
	/// <summary>
	/// True is Recommended (Default : True)
	/// </summary>
	/// <param name="target -> target Actor"></param>
	/// <param name="flag -> Create Joint With JointDef Directly"></param>
	void CreateJointDefWithTarget(Actor* target, const bool& flag = true);

protected:
	using Super = BaseJointComponent;
	virtual void CreateJoint() abstract;
	virtual void SetDefaultProperties(const bool& flag) abstract;

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
	SetDefaultProperties(flag);
}



#ifdef OPT_JOINT_RESET
#define JOINT_RESETOR(_JointComponentType) static_cast<MainMap*>(World::Get()->GetLevel())->ReserveDestroyJoint(joint_);\
static_cast<MainMap*>(World::Get()->GetLevel())->ReserveCreateJoint(std::move(std::bind(&_JointComponentType::CreateJoint, this->component_)));
#endif

#ifdef OPT_JOINT_NONRESET
#define JOINT_RESETOR(_JointComponentType) static_cast<MainMap*>(World::Get()->GetLevel())->ReserveCreateJoint(std::bind(&_JointComponentType::CreateJoint, this->component_));
#endif

#define JOINT_DEF component_->jointDef_

#define RESERVE(_JointType) static_cast<MainMap*>(World::Get()->GetLevel())->ReserveCreateJoint(std::move(std::bind(&_JointType::CreateJoint, this->component_)));
#define DESTROY static_cast<MainMap*>(World::Get()->GetLevel())->ReserveDestroyJoint(joint_);