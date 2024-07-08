#include "AnimationClip.h"

AnimationClip::AnimationClip() :
    triggers_(),
    events_(),
    name_(),
    frames_(),
    is_repeat_(false),
    play_back_speed_(1.f)
{
}

void AnimationClip::MakeTrigger(const std::wstring& kName, const std::wstring& kConnected)
{
    triggers_[kName] = Trigger(false, kConnected);
}

void AnimationClip::SetTrigger(const std::wstring& kName, bool val)
{
    triggers_[kName].val_ = val;
}
