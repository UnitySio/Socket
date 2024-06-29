#include "AnimatorComponent.h"
#include "../Engine/Windows/DX/Sprite.h"
#include "TransformComponent.h"
#include "Time/time.h"

AnimatorComponent::AnimatorComponent(Actor* owner, const std::wstring& kName)
    :ActorComponent(owner, kName), playSpeed_(8.f), timer_(0), sprite_renderer_(nullptr),playing_index_(0)
{
    
}

void AnimatorComponent::Tick(float delta_time)
{
    //Check triggers
    for (auto &var : playing_clip_->triggers_)
    {
        //Trigger is true? & Can it just change to the other clip just now?
        if (var.second.value_ && !var.second.hasExitTime)
        {
            timer_ = 0;
            playing_index_ = 0;

            //If this trigger has function, Excute it
            if (var.second.func_ != nullptr) var.second();

            //Change to target
            playing_clip_ = clips_[var.second.target_clip_];
            break;
        }
    }

    timer_ += delta_time;
    if (timer_ >= 1.f / playing_clip_->playbackSpeed)
    {
        timer_ = 0.f;

        //Animation is not finish
        if (playing_index_ < playing_clip_->include_frames_.size() - 1)
        {
            playing_index_++;
            sprite_renderer_->frame_index_ = playing_clip_->include_frames_[playing_index_];
        }
        //Animation is finish
        else
        {
            //Is Repeat option on?
            if (playing_clip_->isRepeat)
            {
                playing_index_ = 0;
                sprite_renderer_->frame_index_ = playing_clip_->include_frames_[0];
            }

            //Check triggers
            for (auto &var : playing_clip_->triggers_)
            {
                //Trigger is true?
                if (var.second.value_)
                {
                    playing_index_ = 0;
                    if(var.second.func_ != nullptr) var.second();
                    playing_clip_ = clips_[var.second.target_clip_];
                    break;
                }
            }
        }
    }
}

void AnimatorComponent::MakeAnimationClip(std::wstring clipname, int selected[], int size)
{
    std::shared_ptr clip = std::make_shared<AnimationClip>();
    clip->clipName = clipname;
    for (int i = 0; i < size; i++)
    {
        clip->include_frames_.push_back(selected[i]);
    }

    clips_.insert(std::make_pair(clipname, clip));
}

void AnimatorComponent::MakeAnimationClip(std::wstring clipname, int start_index, int end_index)
{
    std::shared_ptr clip = std::make_shared<AnimationClip>();
    clip->clipName = clipname;
    for (int i = start_index; i < end_index; i++)
    {
        clip->include_frames_.push_back(i);
    }

    clips_.insert(std::make_pair(clipname, clip));
}

void AnimatorComponent::ChangeAnimationClip()
{
    
}