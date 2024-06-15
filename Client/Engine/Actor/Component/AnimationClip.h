#pragma once
#include <vector>
#include <string>
#include <map>

template <typename T> class Trigger
{
public:
	Trigger(){}
	Trigger(T val,std::wstring trans_to_this)
	{
		value_ = val;
		hasExitTime = true;
		target_clip_ = trans_to_this;
	}
	std::wstring target_clip_;
	T value_;
	bool hasExitTime;
};

class AnimationClip
{
public:
	AnimationClip();

	void SetRepeat();
	bool GetRepeat();

	void SetPlaySpeed(float speed);
	float GetPlaySpeed();

	void MakeTrigger(std::wstring trigger,std::wstring connected);
	void SetTrigger(std::wstring,bool);
	Trigger<bool> GetTrigger(std::wstring);

	std::map<std::wstring, Trigger<bool>> triggers_;
private:
	friend class AnimatorComponent;
	std::wstring clipName;
	std::vector<int> include_frames_;
	bool isRepeat;
	float playbackSpeed;
};