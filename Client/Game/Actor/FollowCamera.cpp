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
    vertical_offset_(1.f)
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

    Math::Vector2 focus_position = focus_area_->center + Math::Vector2::Up() * vertical_offset_;
    GetTransform()->SetRelativePosition(focus_position);
    
}

void FollowCamera::Tick(float delta_time)
{
    Actor::Tick(delta_time);
    
    AddDebugBox(focus_area_->center, focus_area_size_ / 2.f);
    
}
