#pragma once
#include "Actor/Actor.h"
class Disinteractable : public Actor
{
public:
	Disinteractable(const std::wstring& kName);

protected:
	using Super = Actor;
};

