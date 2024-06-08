#pragma once
#include "../Actor.h"
#include "../Engine/Windows/DX/Sprite.h"

class AnimatorComponent :public ActorComponent
{
public:
	AnimatorComponent(Actor* owner, const std::wstring& kName);
	void Tick(float delta_time);

private:
	float timer_;
	float playSpeed_;
};