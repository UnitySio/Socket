#pragma once
#include "../Actor.h"
#include "Graphics/Sprite.h"
#include "Graphics/AnimationClip.h"

class AnimatorComponent :public ActorComponent
{
public:
	AnimatorComponent(Actor* owner, const std::wstring& kName);
	void PlayAnimation();
	void MakeAnimationClip(std::wstring clipName, std::wstring path);
	void SetAnimationClip(std::wstring clipName);

	std::map<std::wstring, std::shared_ptr<AnimationClip>> clips_;
	std::shared_ptr<AnimationClip> targetClip_;

	std::map<std::wstring, std::vector<std::wstring>> triggers_;

	int frameNumber_;
	float playTime;
};
