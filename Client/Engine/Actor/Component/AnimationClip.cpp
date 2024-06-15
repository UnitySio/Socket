#include <string>
#include "AnimationClip.h"

AnimationClip::AnimationClip()
    :isRepeat(false), playbackSpeed(3.0f)
{
    
}

void AnimationClip::SetRepeat() { isRepeat = !isRepeat; }
bool AnimationClip::GetRepeat() { return isRepeat; }

void AnimationClip::SetPlaySpeed(float speed) { playbackSpeed = speed; }
float AnimationClip::GetPlaySpeed() { return playbackSpeed; }

void AnimationClip::MakeTrigger(std::wstring trigger, std::wstring connected) { triggers_.insert(std::make_pair(trigger, Trigger(false, connected))); }
void AnimationClip::SetTrigger(std::wstring trigger, bool value) { triggers_[trigger].value_ = value; }
Trigger<bool> AnimationClip::GetTrigger(std::wstring trigger) { return triggers_[trigger]; }