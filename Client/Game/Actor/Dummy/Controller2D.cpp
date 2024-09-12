#include "pch.h"
#include "Controller2D.h"

#include "DebugDrawHelper.h"
#include "Actor/Component/BoxColliderComponent.h"
#include "Math/Bounds.h"
#include "Math/Math.h"

Controller2D::Controller2D(const std::wstring& kName) :
    Actor(kName),
    skin_width_(.015f),
    horizontal_ray_count_(4),
    vertical_ray_count_(4),
    horizontal_ray_spacing_(0.f),
    vertical_ray_spacing_(0.f),
    raycast_origins_()
{
    box_collider_ = AddComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({1.f, 1.f});
}

void Controller2D::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    UpdateRaycastOrigins();
    CalculateRaySpecing();
    
    Bounds bounds = box_collider_->GetBounds();
    bounds.Expand(skin_width_ * -2.f);

    DebugDrawHelper::Get()->DrawBox(bounds.center, bounds.size, Math::Color::Green);

    for (int i = 0; i < vertical_ray_count_; ++i)
    {
        Math::Vector2 start = raycast_origins_.bottom_left + Math::Vector2::Right() * vertical_ray_spacing_ * i;
        Math::Vector2 end = start + Math::Vector2::Up() * -2.f;

        DebugDrawHelper::Get()->DrawSegment(start, end, Math::Color::Red);
    }
}

void Controller2D::UpdateRaycastOrigins()
{
    Bounds bounds = box_collider_->GetBounds();
    bounds.Expand(skin_width_ * -2.f);

    raycast_origins_.bottom_left = bounds.min;
    raycast_origins_.bottom_right = {bounds.max.x, bounds.min.y};
    raycast_origins_.top_left = {bounds.min.x, bounds.max.y};
    raycast_origins_.top_right = bounds.max;
}

void Controller2D::CalculateRaySpecing()
{
    Bounds bounds = box_collider_->GetBounds();
    bounds.Expand(skin_width_ * -2.f);

    horizontal_ray_count_ = Math::Clamp(horizontal_ray_count_, 2, 1024);
    horizontal_ray_count_ = Math::Clamp(horizontal_ray_count_, 2, 1024);

    horizontal_ray_spacing_ = bounds.size.y / (horizontal_ray_count_ - 1);
    vertical_ray_spacing_ = bounds.size.x / (vertical_ray_count_ - 1);
}
