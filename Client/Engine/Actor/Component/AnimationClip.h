#pragma once
#include <vector>
#include <string>

class AnimationClip
{
public:
	AnimationClip(std::wstring path);

	void SetRepeat();
	bool GetRepeat();

	void SetPlaySpeed(float speed);
	float GetPlaySpeed();
private:
	friend class AnimatorComponent;
	std::wstring clipName;
	bool isRepeat;
	bool hasExitTime;
	float playbackSpeed;
};