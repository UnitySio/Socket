#pragma once
#include <map>
#include <memory>
#include "Actor/Component/ActorComponent.h"
#include "Misc/EngineMacros.h"

class AnimationClip;
class SpriteRendererComponent;
class AnimationEvent;

class AnimatorComponent : public ActorComponent
{
public:
    AnimatorComponent(class Actor* owner, const std::wstring& kName);
    virtual ~AnimatorComponent() override = default;

    virtual void BeginPlay() override;
    virtual void TickComponent(float delta_time) override;

    std::shared_ptr<AnimationClip> AddClip(const std::wstring& kName, int* sprite_idx_arr, int size);
    inline std::shared_ptr<AnimationClip> GetClip(std::wstring clip_name) { return clips_[clip_name]; }
    inline bool PlayClip(std::wstring clip_name) 
    { 
        if (clips_[clip_name] == current_clip_) return false;
        current_clip_ = clips_[clip_name]; 
    }
    inline bool PlayClip(std::shared_ptr<AnimationClip> clip)
    { 
        if (clip == current_clip_) return false;
        current_clip_ = clip;
    }

    template<typename L>
    inline void AddEndEvent(L&& lamda)
    {
        end_event_ = std::make_shared<AnimationEvent>(AnimationEvent(std::move(Function<void(void)>(std::move(lamda)))));
    }

private:
    SpriteRendererComponent* sprite_renderer_;

    std::map<std::wstring, std::shared_ptr<AnimationClip>> clips_;
    std::shared_ptr<AnimationClip> current_clip_;
    std::shared_ptr<AnimationEvent> end_event_;

    float timer_;
    int current_index_;
};