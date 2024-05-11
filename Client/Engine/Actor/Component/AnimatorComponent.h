#pragma once
#include "../Actor.h"
#include "Graphics/Sprite.h"

struct AnimationClip
{
	std::wstring clipName_;
	bool isRepeat;
	float playbackSpeed;
	int frameNumber_,maxFrame_;
	int firstIndex_,lastIndex_;
	std::wstring connected_OtherClip_;

	AnimationClip(std::wstring clipName,int firstIndex, int lastIndex);
	void SetPlaySpeed(float speed) {playbackSpeed = speed;}
	void ConnectToOther(std::wstring clipName);
	bool TransToOther(std::wstring clipName);
};

class AnimatorComponent :public ActorComponent
{
public:
	AnimatorComponent(Actor* owner, const std::wstring& kName);
	void PlayAnimation();
	void MakeAnimationClip(std::wstring clipName, int firstIndex, int lastIndex);
	bool SetAnimationClip(std::wstring clipName, float speed);
	bool SetAnimationClip(int index);//¹Ì±¸Çö
private:
	std::unique_ptr<Sprite> originSheet_;
	std::vector<std::unique_ptr<AnimationClip>> clips_;
	AnimationClip* targetClip_;

	int frameNumber_;
	float playTime;
};
