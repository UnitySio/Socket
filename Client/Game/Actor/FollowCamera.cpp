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
    limit_width_(0.f),
    limit_height_(0.f),
    follow_offset(Math::Vector2::Zero())
{
    camera_ = CreateComponent<CameraComponent>(L"Camera");
}

void FollowCamera::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    if (follow_)
    {
        const Math::Vector2 location = GetTransform()->GetRelativeLocation();
        
        Math::Vector2 target_location = follow_->GetTransform()->GetRelativeLocation();
        Math::Vector2 new_position = Math::Vector2::Lerp(location, target_location + follow_offset, delta_time * 2.f);
        
        width_ = camera_->GetAspect();
        height_ = camera_->GetSize();

        float limit_x = limit_width_ - width_;
        if (limit_x < 0.f) limit_x = width_;
        
        float clamp_x = std::clamp(new_position.x, -limit_x, limit_x);
        
        float limit_y = limit_height_ - height_;
        if (limit_y < 0.f) limit_y = height_;
        
        float clamp_y = std::clamp(new_position.y, -limit_y, limit_y);
        
        GetTransform()->SetRelativeLocation({ clamp_x, clamp_y });;
    }
    
}
