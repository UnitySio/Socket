#include "FollowCamera.h"

#include <algorithm>

#include "Actor/Component/CameraComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Audio/AudioManager.h"

FollowCamera::FollowCamera(const std::wstring& kName) :
    Actor(kName),
    follow_(nullptr),
    width_(0.f),
    height_(0.f),
    limit_width_(40.f),
    limit_height_(10.f),
    follow_offset(Math::Vector2::Zero())
{
    camera_ = CreateComponent<CameraComponent>(L"Camera");
}

void FollowCamera::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    if (follow_)
    {
        const Math::Vector2 position = GetTransform()->GetRelativePosition();
        
        Math::Vector2 target_position = follow_->GetTransform()->GetRelativePosition();
        Math::Vector2 new_position = Math::Vector2::Lerp(position, target_position + follow_offset, delta_time * 2.f);
        
        width_ = camera_->GetAspect();
        height_ = camera_->GetSize();

        float limit_x = limit_width_ - width_;
        if (limit_x < 0.f) limit_x = width_;
        
        float clamp_x = std::clamp(new_position.x, -limit_x, limit_x);
        
        float limit_y = limit_height_ - height_;
        if (limit_y < 0.f) limit_y = height_;
        
        float clamp_y = std::clamp(new_position.y, -limit_y, limit_y);
        
        GetTransform()->SetRelativePosition({ clamp_x, clamp_y });;
    }
    
}
