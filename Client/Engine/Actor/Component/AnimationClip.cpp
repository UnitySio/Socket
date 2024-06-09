#include <string>
#include "AnimationClip.h"

AnimationClip::AnimationClip()
    :isRepeat(false), hasExitTime(true), playbackSpeed(3.0f)
{
    
}

void AnimationClip::SetRepeat() { isRepeat = !isRepeat; }
bool AnimationClip::GetRepeat() { return isRepeat; }

void AnimationClip::SetPlaySpeed(float speed) { playbackSpeed = speed; }
float AnimationClip::GetPlaySpeed() { return playbackSpeed; }