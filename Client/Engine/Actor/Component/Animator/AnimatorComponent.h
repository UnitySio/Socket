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

    void AddClip(const std::wstring& kName, int* selected, int size);

private:
    // 테스트 후 제거 요망
    friend class PlayerController;
    
    SpriteRendererComponent* sprite_renderer_;

    std::map<std::wstring, std::shared_ptr<AnimationClip>> clips_;
    std::shared_ptr<AnimationClip> current_clip_;
    
    float timer_;
    int current_index_;
    
};
