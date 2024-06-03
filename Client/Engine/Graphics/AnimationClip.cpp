#include <string>
#include "Graphics/Graphics.h"
#include "Graphics/AnimationClip.h"

AnimationClip::AnimationClip(std::wstring path)
    :originSheet_(nullptr),isRepeat(false),hasExitTime(true),playbackSpeed(3.0f)
{
    originSheet_ = std::make_unique<Sprite>();
    Graphics* gfx = Graphics::Get();
    assert(originSheet_->Load(gfx->GetD3DDevice(), path));
    originSheet_->Split(3, 15, { .5f, 0.f });

    includeFrames_.clear();
}

void AnimationClip::SetIncludeFrames(int selectedFrame[],int size)
{
    for (int i = 0;i < size;i++)
    {
        includeFrames_.push_back(selectedFrame[i]);
    }
}

void AnimationClip::SetIncludeFrames(int startIndex,int endIndex)
{
    for (int i = startIndex;i < endIndex;i++)
    {
        includeFrames_.push_back(i);
    }
}

void AnimationClip::SetRepeat() { isRepeat = !isRepeat; }
bool AnimationClip::GetRepeat() { return isRepeat; }

void AnimationClip::SetPlaySpeed(float speed) { playbackSpeed = speed; }
float AnimationClip::GetPlaySpeed() { return playbackSpeed; }

int AnimationClip::GetAnimationLength() { return includeFrames_.size(); }
int AnimationClip::GetAnimationIndex(int idx) { return includeFrames_[idx]; }