#include "FollowCamera.h"

#include <algorithm>

#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/CameraComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Pawn.h"
#include "Misc/Debug.h"

FollowCamera::FollowCamera(const std::wstring& kName) :
    Actor(kName),
    target_(nullptr),
    box_collider_(nullptr),
    focus_area_(nullptr),
    focus_area_size_({3.f, 5.f}),
    vertical_offset_(1.f),
    half_width_(0),
    half_height_(0),
    limit_half_width_(0),
    limit_half_height_(0)
{
    camera_ = CreateComponent<CameraComponent>(L"Camera");
}

void FollowCamera::BeginPlay()
{
    Actor::BeginPlay();

    Pawn* pawn = dynamic_cast<Pawn*>(target_);
    if (pawn)
    {
        box_collider_ = pawn->GetBoxCollider();
        if (box_collider_)
        {
            Bounds bounds = box_collider_->GetBounds();
            focus_area_ = MAKE_UNIQUE<FocusArea>(bounds, focus_area_size_);
        }
    }
    
}

void FollowCamera::PhysicsTick(float delta_time)
{
    Actor::PhysicsTick(delta_time);
    
    Bounds bounds = box_collider_->GetBounds();
    focus_area_->Tick(bounds);

    const Math::Vector2 position = GetTransform()->GetWorldPosition();

    Math::Vector2 focus_position = focus_area_->center + Math::Vector2::Up() * vertical_offset_;
    Math::Vector2 new_position = Math::Vector2::Lerp(position, focus_position, delta_time * 2.f);
        
    half_width_ = camera_->GetAspect();
    half_height_ = camera_->GetSize();

    float limit_x = limit_half_width_ - half_width_;
    if (limit_x < 0.f) limit_x = half_width_;
        
    float clamp_x = std::clamp(new_position.x, -limit_x, limit_x);
        
    float limit_y = limit_half_height_ - half_width_;
    if (limit_y < 0.f) limit_y = half_width_;
        
    float clamp_y = std::clamp(new_position.y, -limit_y, limit_y);
    GetTransform()->SetRelativePosition({ clamp_x, clamp_y });;
    
}

void FollowCamera::Tick(float delta_time)
{
    Actor::Tick(delta_time);
    
    AddDebugBox(focus_area_->center, focus_area_size_ / 2.f);
    
}
