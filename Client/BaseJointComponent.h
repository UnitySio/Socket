#pragma once
#include "../Engine/Actor/Component/ActorComponent.h"

template<typename T>
class BaseJointComponent : public ActorComponent
{
public:
	BaseJointComponent(class Actor* owner, const std::wstring& kName) :
		ActorComponent(owner, kName)
	{};
	virtual ~BaseJointComponent() {};




protected:
	T* joint_;


};

