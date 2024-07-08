#pragma once
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

    void MakeAnimationClip(const std::wstring& kName, int* selected, int size);
    void MakeAnimationClip(const std::wstring& kName, int start_index, int end_index);

private:
    // 테스트 후 제거 요망
    friend class PlayerController;
    
    SpriteRendererComponent* sprite_renderer_;

    std::map<std::wstring, SHARED_PTR<AnimationClip>> clips_;
    SHARED_PTR<AnimationClip> current_clip_;
    
    float timer_;
    float play_speed_;

    int current_index_;
    
};
