﻿#include "pch.h"
#include "AnimatorComponent.h"

#include "AnimationClip.h"
#include "Actor/Actor.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "rttr/registration.h"

AnimatorComponent::AnimatorComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    sprite_renderer_(nullptr),
    clips_(),
    timer_(0.f),
    current_index_(0),
    is_playing_(false)
{
    current_clip_ = nullptr;
}

void AnimatorComponent::BeginPlay()
{
    ActorComponent::BeginPlay();
    
    SpriteRendererComponent* sprite_renderer = GetOwner()->GetComponent<SpriteRendererComponent>();
    if (sprite_renderer) sprite_renderer_ = sprite_renderer;
}

void AnimatorComponent::TickComponent(float delta_time)
{
    ActorComponent::TickComponent(delta_time);
    if (!sprite_renderer_) return;

    if (is_playing_)
    {
        timer_ += delta_time;
        if (timer_ >= 1.f / current_clip_->GetFrameRate())
        {
            if (current_clip_->events_.contains(current_index_)) current_clip_->events_[current_index_]();
            if (current_clip_->is_repeat_ || current_index_ < current_clip_->frames_.size() - 1)
            {
                current_index_ = (current_index_ + 1) % current_clip_->frames_.size();
                sprite_renderer_->frame_index_ = current_clip_->frames_[current_index_];
            
                timer_ -= 1.f / current_clip_->GetFrameRate();
            }
            else
            {
                is_playing_ = false;
                timer_ = 0.f;
                current_index_ = 0;
            }
        }
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
    current_clip_ = clips_[clip_name];
    is_playing_ = true;
    timer_ = 0.f;
    current_index_ = 0;
    return true;
}

bool AnimatorComponent::PlayClip(std::shared_ptr<AnimationClip> clip)
{
    if (clip == current_clip_) return false;
    current_clip_ = clip;
    is_playing_ = true;
    timer_ = 0.f;
    current_index_ = 0;
    return true;
}

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<AnimatorComponent>("AnimatorComponent")
        .constructor<Actor*, const std::wstring&>();
}