#include "pch.h"
#include "RayCastController.h"

#include "Actor/Component/ColliderComponent.h"
#include "Math/Bounds.h"
#include "Math/Math.h"

RayCastController::RayCastController(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    skin_width_(.015f),
    collider_(nullptr),
    horizontal_ray_count_(4),
    vertical_ray_count_(4),
    horizontal_ray_spacing_(0.f),
    vertical_ray_spacing_(0.f),
    raycast_origins_()
{
}

void RayCastController::BeginPlay()
{
    ActorComponent::BeginPlay();
    
    CalculateRaySpecing();
}

void RayCastController::UpdateRaycastOrigins()
{
    Bounds bounds = collider_->GetBounds();
    bounds.Expand(skin_width_ * -2.f);

    raycast_origins_.bottom_left = bounds.min;
    raycast_origins_.bottom_right = {bounds.max.x, bounds.min.y};
    raycast_origins_.top_left = {bounds.min.x, bounds.max.y};
    raycast_origins_.top_right = bounds.max;
}

void RayCastController::CalculateRaySpecing()
{
    Bounds bounds = collider_->GetBounds();
    bounds.Expand(skin_width_ * -2.f);

    horizontal_ray_count_ = Math::Clamp(horizontal_ray_count_, 2, 1024);
    horizontal_ray_count_ = Math::Clamp(horizontal_ray_count_, 2, 1024);

    horizontal_ray_spacing_ = bounds.size.y / (horizontal_ray_count_ - 1);
    vertical_ray_spacing_ = bounds.size.x / (vertical_ray_count_ - 1);
}
