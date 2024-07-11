﻿#pragma once
#include <map>

#include "Actor/Component/ActorComponent.h"
#include "Misc/EngineMacros.h"

class AnimationClip;
class SpriteRendererComponent;

class AnimatorComponent : public ActorComponent
{
public:
    AnimatorComponent(class Actor* owner, const std::wstring& kName);
    virtual ~AnimatorComponent() override = default;

    virtual void BeginPlay() override;
    virtual void TickComponent(float delta_time) override;

    void AddClip(const std::wstring& kName, int* sprite_idx_arr, int size);
    inline SHARED_PTR<AnimationClip> GetClip(std::wstring clip_name) { return clips_[clip_name]; }
    void PlayClip(std::wstring clip_name);

private:
    SpriteRendererComponent* sprite_renderer_;

    std::map<std::wstring, SHARED_PTR<AnimationClip>> clips_;
    SHARED_PTR<AnimationClip> current_clip_;
    float timer_;
    int current_index_;
    
};
