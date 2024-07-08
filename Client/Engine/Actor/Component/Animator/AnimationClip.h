#pragma once
#include <map>
#include <string>
#include <vector>

#include "Misc/EngineMacros.h"
#include "Misc/Function.h"

template <typename T>
class Trigger
{
public:
    Trigger() :
        has_exit_time_(false)
    {
    }

    ~Trigger() = default;

    Trigger(T val, const std::wstring& kName) :
        val_(val),
        name_(kName),
        has_exit_time_(true)
    {
    }

    template <typename Ret, typename... Args>
    Trigger(T val, const std::wstring& kClipName, Function<Ret(Args...)>&& func)
    {
        val_ = val;
        name_ = kClipName;
        has_exit_time_ = true;
        func_ = MAKE_SHARED<Function<void(void)>>(std::forward<Function<Ret(Args...)>>(func));
    }

    void operator()() const
    {
        (*func_)();
    }

private:
    friend class AnimationClip;
    friend class AnimatorComponent;
    
    std::wstring name_;
    T val_;
    bool has_exit_time_;
    SHARED_PTR<Function<void(void)>> func_;
};

class AnimationEvent
{
public:
    AnimationEvent() = default;
    ~AnimationEvent() = default;

    template <typename Ret, typename... Args>
    AnimationEvent(Function<Ret(Args...)>&& func)
    {
        func_ = MAKE_SHARED<Function<void(void)>>(std::forward<Function<Ret(Args...)>>(func));
    }

    void operator()() const
    {
        (*func_)();
    }

private:
    SHARED_PTR<Function<void(void)>> func_;
};

class AnimationClip
{
public:
    AnimationClip();
    ~AnimationClip() = default;

    template <typename Ret, typename... Args>
    void MakeTrigger(const std::wstring& kName, const std::wstring& kConnected, Function<Ret(Args...)>&& func);

    void MakeTrigger(const std::wstring& kName, const std::wstring& kConnected);
    void SetTrigger(const std::wstring& kName, bool val);
    
    template <typename Ret, typename... Args>
    void MakeEvent(int frame, Function<Ret(Args...)>&& func);

    inline void SetRepeat(bool is_repeat) { is_repeat_ = is_repeat; }
    inline void SetPlayBackSpeed(float play_back_speed) { play_back_speed_ = play_back_speed; }

    inline bool IsRepeat() const { return is_repeat_; }
    inline float GetPlayBackSpeed() const { return play_back_speed_; }

private:
    friend class AnimatorComponent;
    
    std::map<std::wstring, Trigger<bool>> triggers_;
    std::map<int, AnimationEvent> events_;

    std::wstring name_;
    std::vector<int> frames_;
    bool is_repeat_;
    float play_back_speed_;
};

template <typename Ret, typename... Args>
void AnimationClip::MakeTrigger(const std::wstring& kName, const std::wstring& kConnected, Function<Ret(Args...)>&& func)
{
    triggers_[kName] = Trigger(false, kConnected, std::forward<Function<Ret(Args...)>>(func));
}

template <typename Ret, typename ... Args>
void AnimationClip::MakeEvent(int frame, Function<Ret(Args...)>&& func)
{
    events_[frame] = AnimationEvent(std::forward<Function<Ret(Args...)>>(func));
}
