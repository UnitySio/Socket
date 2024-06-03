#pragma once
#include <vector>
#include <string>
#include "Graphics/Sprite.h"

class AnimationClip
{
public:
	AnimationClip(std::wstring path);

	void SetRepeat();
	bool GetRepeat();

	void SetPlaySpeed(float speed);
	float GetPlaySpeed();

	int GetAnimationLength();
	int GetAnimationIndex(int idx);

	std::wstring GetClipName() { return clipName; }

	void SetIncludeFrames(int selectedFrame[], int size);
	void SetIncludeFrames(int startIndex, int endIndex);

	std::unique_ptr<Sprite> originSheet_;

private:
	friend class AnimatorComponent;
	std::wstring clipName;
	bool isRepeat;
	bool hasExitTime;
	float playbackSpeed;

	std::vector<int> includeFrames_;
};