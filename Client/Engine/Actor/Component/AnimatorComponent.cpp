#include "AnimatorComponent.h"
#include "../Engine/Windows/DX/Sprite.h"
#include "TransformComponent.h"
#include "Time/time.h"

AnimatorComponent::AnimatorComponent(Actor* owner, const std::wstring& kName)
    :ActorComponent(owner, kName), playSpeed_(8.f)
{
    
}

void AnimatorComponent::Tick(float delta_time)
{
    timer_ += delta_time;
    if (timer_ >= 1.f / playSpeed_)
    {
        //frame_index_ = (frame_index_ + 1) % 6;
        timer_ = 0.f;
    }
}