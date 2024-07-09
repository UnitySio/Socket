#include "AnimationClip.h"

AnimationClip::AnimationClip() :
    events_(),
    name_(),
    frames_(),
    is_repeat_(false),
    frame_rate_(1.f)
{
}

template <typename Ret, typename ... Args>
void AnimationClip::AddEvent(int frame, Function<Ret(Args...)>&& func)
{
    events_[frame] = AnimationEvent(std::forward<Function<Ret(Args...)>>(func));
}
