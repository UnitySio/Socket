#pragma once
#include "../Engine/Actor/Component/ActorComponent.h"
#include "../Engine/Actor/Actor.h"
#include "../Engine/Level/World.h"
#include "box2d.h"
#include <type_traits>

template<typename T, typename U>
class BaseJointComponent : public ActorComponent
{
public:
	BaseJointComponent(class Actor* owner, const std::wstring& kName) :
		ActorComponent(owner, kName),
		joint_(nullptr),
		jointDef_(nullptr),
		owner_(owner),
		world_(World::Get()->physics_world_.get())
	{};
	virtual ~BaseJointComponent() {};

	T* GetJoint() { return joint_; }
	U* GetJointDef() { return jointDef_; }
	void SetJointDef(U* input) { jointDef_ = input; }


	void CreateJointDef(Actor* target);

protected:
	T* joint_;
	U* jointDef_;
	Actor* owner_;
	b2World* world_;
};

template<typename T, typename U>
inline void BaseJointComponent<T, U>::CreateJointDef(Actor* target)
{
	jointDef_ = new U;
	jointDef_->bodyA = owner_->body_;
	jointDef_->bodyB = target->body_;

	joint_ = static_cast<T*>(world_->CreateJoint(jointDef_));

	joint_->SetJoint(joint_);
	joint_->SetJointDef(jointDef_);
}
