#pragma once
#include <vector>
#include <string>

class AnimationClip
{
public:
	AnimationClip();

	void SetRepeat();
	bool GetRepeat();

	void SetPlaySpeed(float speed);
	float GetPlaySpeed();

private:
	friend class AnimatorComponent;
	std::wstring clipName;
	std::vector<int> include_frames_;
	bool isRepeat;
	bool hasExitTime;
	float playbackSpeed;
};