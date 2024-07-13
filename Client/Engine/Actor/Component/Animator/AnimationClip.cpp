#include "AnimationClip.h"

AnimationClip::AnimationClip() :
    events_(),
    frames_(),
    is_repeat_(false),
    frame_rate_(1.f)
{
}

template<>
void AnimationClip::AddEvent(int frame, Function<void(void)>&& func)
{
    events_[frame] = AnimationEvent(std::forward<Function<void(void)>>(func));
}

void AnimationClip::DelEvent(int frame)
{
    events_.erase(frame);
}