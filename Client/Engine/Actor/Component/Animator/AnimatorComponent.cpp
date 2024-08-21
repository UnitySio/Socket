#include "pch.h"
#include "AnimatorComponent.h"

#include <ranges>

#include "AnimationClip.h"
#include "Actor/Actor.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Logger/Logger.h"

AnimatorComponent::AnimatorComponent(Actor* owner, const std::wstring& kName) :
    Super(owner, kName),
    sprite_renderer_(nullptr),
    clips_(),
    timer_(0.f),
    current_index_(0)
{
    current_clip_ = nullptr;
}

void AnimatorComponent::BeginPlay()
{
    Super::BeginPlay();
    
    SpriteRendererComponent* sprite_renderer = GetOwner()->GetComponent<SpriteRendererComponent>();
    if (sprite_renderer) sprite_renderer_ = sprite_renderer;
}

void AnimatorComponent::TickComponent(float delta_time)
{
    Super::TickComponent(delta_time);
    if (!sprite_renderer_) return;

    timer_ += delta_time;
    if (timer_ >= 1.f / current_clip_->GetFrameRate())
    {
        timer_ = 0.f; 
        //if (!IsPlaying()) LOG(L"Animation is end");
        if (current_index_ < current_clip_->frames_.size() - 1)
        {
            is_playing_ = true;
            current_index_++;
            sprite_renderer_->frame_index_ = current_clip_->frames_[current_index_];
        }
        else if(current_clip_->is_repeat_)
        {
            current_index_ = 0;
            sprite_renderer_->frame_index_ = current_clip_->frames_[0];
        }
        else
        {
            is_playing_ = false;
            return;
        }

        if (current_clip_->events_.contains(current_index_)) current_clip_->events_[current_index_]();
    }
}

std::shared_ptr<AnimationClip> AnimatorComponent::AddClip(const std::wstring& kName, int* sprite_idx_arr, int size)
{
    std::shared_ptr<AnimationClip> clip = std::make_shared<AnimationClip>();

    for (int i = 0; i < size; i++)
    {
        clip->frames_.push_back(sprite_idx_arr[i]);
    }
    clips_[kName] = clip;

    return clip;
}

bool AnimatorComponent::PlayClip(std::wstring clip_name)
{
    if (clips_[clip_name] == current_clip_) return false;
    current_index_ = 0;
    current_clip_ = clips_[clip_name];
    return true;
}

bool AnimatorComponent::PlayClip(std::shared_ptr<AnimationClip> clip)
{
    if (clip == current_clip_) return false;
    current_index_ = 0;
    current_clip_ = clip;
    return true;
}