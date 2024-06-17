#pragma once
#include <vector>
#include <string>
#include <map>
#include "Misc/Function.h"

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

	template<typename Ret, typename... Args>
	Trigger(T val, std::wstring trans_to_this, Function<Ret(Args...)>&& func)
	{
		value_ = val;
		hasExitTime = true;
		target_clip_ = trans_to_this;
		func_ = std::make_shared<Function<void(void)>>(std::forward<Function<Ret(Args...)>>(func));
	}

	void operator()()
	{
		(*func_)();
	}

	std::wstring target_clip_;
	T value_;
	bool hasExitTime;
	std::shared_ptr<Function<void(void)>> func_;
};

class AnimationClip
{
public:
	AnimationClip();

	void SetRepeat();
	bool GetRepeat();

	void SetPlaySpeed(float speed);
	float GetPlaySpeed();

	template<typename Ret, typename... Args>
	void MakeTrigger(std::wstring trigger,std::wstring connected, Function<Ret(Args...)>&& func);
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

template<typename Ret, typename ...Args>
inline void AnimationClip::MakeTrigger(std::wstring trigger, std::wstring connected, Function<Ret(Args...)>&& func)
{
	triggers_.insert(std::make_pair(trigger, Trigger(false, connected, std::forward<Function<Ret(Args...)>>(func))));
}
