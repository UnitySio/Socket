#pragma once
#include <map>
#include <string>
#include <vector>

#include "Misc/EngineMacros.h"
#include "Misc/Function.h"

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
    void AddEvent(int frame, Function<Ret(Args...)>&& func);

    inline void SetRepeat(bool is_repeat) { is_repeat_ = is_repeat; }
    inline bool GetRepeat() const { return is_repeat_; }

    inline void SetFrameRate(float frame_per_sec) { frame_rate_ = frame_per_sec; }
    inline float GetFrameRate() const { return frame_rate_; }

private:
    friend class AnimatorComponent;
    
    std::map<int, AnimationEvent> events_;

    std::wstring name_;
    std::vector<int> frames_;
    bool is_repeat_;
    float frame_rate_;
};
