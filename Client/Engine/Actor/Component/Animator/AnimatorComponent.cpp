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
    play_speed_(1.f),
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

    for (const auto& val : current_clip_->triggers_ | std::views::values)
    {
        if (val.val_ && !val.has_exit_time_)
        {
            timer_ = 0.f;
            current_index_ = 0;

            if (val.func_) val();

            current_clip_ = clips_[val.name_];
            break;
        }
    }

    if (current_clip_->events_.contains(current_index_))
    {
        current_clip_->events_[current_index_]();
    }

    timer_ += delta_time;
    if (timer_ >= 1.f / current_clip_->GetPlayBackSpeed())
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

            for (const auto& val : current_clip_->triggers_ | std::views::values)
            {
                if (val.val_ && val.has_exit_time_)
                {
                    current_index_ = 0;

                    if (val.func_) val();

                    current_clip_ = clips_[val.name_];
                    break;
                }
            }
        }
    }
}

void AnimatorComponent::MakeAnimationClip(const std::wstring& kName, int* selected, int size)
{
    SHARED_PTR<AnimationClip> clip = MAKE_SHARED<AnimationClip>();
    clip->name_ = kName;

    for (int i = 0; i < size; i++)
    {
        clip->frames_.push_back(selected[i]);
    }

    clips_[kName] = clip;
}

void AnimatorComponent::MakeAnimationClip(const std::wstring& kName, int start_index, int end_index)
{
    SHARED_PTR<AnimationClip> clip = MAKE_SHARED<AnimationClip>();
    clip->name_ = kName;

    for (int i = start_index; i <= end_index; i++)
    {
        clip->frames_.push_back(i);
    }

    clips_[kName] = clip;
}
