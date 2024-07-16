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
        func_ = std::make_shared<Function<void(void)>>(std::forward<Function<Ret(Args...)>>(func));
    }

    template <typename M>
    AnimationEvent(M* target, Function<void(void)>&& func)
    {
        func_ = std::make_shared<Function<void(void)>>(Function<void(void)>(target, func));
    }

    void operator()() const
    {
        (*func_)();
    }

private:
    std::shared_ptr<Function<void(void)>> func_;
};

class AnimationClip
{
public:
    AnimationClip();
    ~AnimationClip() = default;

    template <typename Ret, typename... Args>
    void AddEvent(int frame, Function<Ret(Args...)>&& func);
    void AddEvent(void(*func)(void), int frame);

    template<typename M>
    void AddEvent(M* target,  void(M::* func)(void), int frame);

    template<typename M>
    void AddEvent(M* target, void(M::* func)(void) const, int frame);

    template<typename L>
    void AddEvent(L&& lamda, int frame);

    void DelEvent(int frame);

    inline const std::vector<int>& GetFrames() { return frames_; }
    inline void AddFrame(int frame_idx) { frames_.push_back(frame_idx); }

    inline void SetRepeat(bool is_repeat) { is_repeat_ = is_repeat; }
    inline bool GetRepeat() const { return is_repeat_; }

    inline void SetFrameRate(float frame_per_sec) { frame_rate_ = frame_per_sec; }
    inline float GetFrameRate() const { return frame_rate_; }

private:
    friend class AnimatorComponent;
    
    std::map<int, AnimationEvent> events_;
    std::vector<int> frames_;
    bool is_repeat_;
    float frame_rate_;
};

template<typename M>
void AnimationClip::AddEvent(M* target, void(M::* func)(void), int frame)
{
    events_[frame] = AnimationEvent(std::move(Function<void(void)>(target, func)));
}

template<typename M>
void AnimationClip::AddEvent(M* target, void(M::* func)(void) const, int frame)
{
    events_[frame] = AnimationEvent(std::move(Function<void(void)>(target, func)));
}

template<typename L>
void AnimationClip::AddEvent(L&& lamda, int frame)
{
    events_[frame] = AnimationEvent(std::move(Function<void(void)>(std::move(lamda))));
}