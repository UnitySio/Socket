#pragma once
#include "../Engine/Actor/Component/ActorComponent.h"
#include "../Client/Include/box2d/box2d.h"
#include <type_traits>

template<typename T, typename U>
class BaseJointComponent : public ActorComponent
{
	static_assert(std::is_base_of<b2Joint, T>::value);
	static_assert(std::is_base_of<b2JointDef, U>::value);
public:
	BaseJointComponent(class Actor* owner, const std::wstring& kName) :
		ActorComponent(owner, kName),
		joint_(nullptr),
		jointDef_(nullptr)
	{};
	virtual ~BaseJointComponent() {};

	T* GetJoint() { return joint_; }
	U* GetJointDef() { return jointDef_; }
	void SetJointDef(U* input) { jointDef_ = input; }

	void CreateJointDef(Actor* target);

protected:
	T* joint_;
	U* jointDef_;

};

template<typename T, typename U>
inline void BaseJointComponent<T, U>::CreateJointDef(Actor* target)
{


	jointDef_ = new U;
	
}
