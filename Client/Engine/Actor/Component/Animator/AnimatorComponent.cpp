#include "AnimatorComponent.h"

#include <ranges>

#include "AnimationClip.h"
#include "Actor/Actor.h"
#include "Actor/Component/SpriteRendererComponent.h"

AnimatorComponent::AnimatorComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    sprite_renderer_(nullptr),
    clips_(),
    current_clip_(nullptr),
    timer_(0.f),
    current_index_(0)
{
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

    

    if (current_clip_->events_.contains(current_index_))
    {
        current_clip_->events_[current_index_]();
    }

    timer_ += delta_time;
    if (timer_ >= 1.f / current_clip_->GetFrameRate())
    {
        timer_ = 0.f;

        if (current_index_ < current_clip_->frames_.size() - 1)
        {
            current_index_++;
            sprite_renderer_->frame_index_ = current_clip_->frames_[current_index_];
        }
        else
        {
            if (current_clip_->is_repeat_)
            {
                current_index_ = 0;
                sprite_renderer_->frame_index_ = current_clip_->frames_[0];
            }
        }
    }
}

void AnimatorComponent::AddClip(const std::wstring& kName, int* sprite_idx_arr, int size)
{
    SHARED_PTR<AnimationClip> clip = MAKE_SHARED<AnimationClip>();

    for (int i = 0; i < size; i++)
    {
        clip->frames_.push_back(sprite_idx_arr[i]);
    }

    clips_[kName] = clip;
}

void AnimatorComponent::PlayClip(std::wstring clip_name)
{
    current_clip_ = clips_[clip_name];
}