#pragma once
#include "../Actor.h"
#include "Graphics/Sprite.h"

struct AnimationClip
{
	std::unique_ptr<Sprite> Image;
	bool isRepeat;
	float playbackSpeed;
	int firstIndex_,lastIndex_;

	AnimationClip(/*int firstIndex, int lastIndex*/);
};

class AnimatorComponent :public ActorComponent
{
public:
	AnimatorComponent(Actor* owner, const std::wstring& kName);
	void PlayAnimation();
	void SetAnimationClip();
private:
	std::unique_ptr<AnimationClip> clip_;
	int frameNumber_;
	float playTime;
};
