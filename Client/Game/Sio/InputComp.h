#pragma once
#include "Actor/Component/ActorComponent.h"

class Actor;

class InputComp : public ActorComponent
{
public:
	InputComp(Actor* owner, const std::wstring& kName);
};

