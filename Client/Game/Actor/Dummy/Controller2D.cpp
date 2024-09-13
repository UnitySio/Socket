#include "pch.h"
#include "Controller2D.h"

#include "DebugDrawHelper.h"
#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Math/Bounds.h"
#include "Math/Math.h"
#include "Physics/Physics2D.h"

Controller2D::Controller2D(const std::wstring& kName) :
    Actor(kName),
    skin_width_(.015f),
    horizontal_ray_count_(4),
    vertical_ray_count_(4),
    horizontal_ray_spacing_(0.f),
    vertical_ray_spacing_(0.f),
    raycast_origins_(),
    collisions_()
{
    box_collider_ = AddComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({1.f, 1.f});
}

void Controller2D::BeginPlay()
{
    Actor::BeginPlay();

    CalculateRaySpecing();
}

void Controller2D::Tick(float delta_time)
{
    Actor::Tick(delta_time);
    
    Bounds bounds = box_collider_->GetBounds();
    bounds.Expand(skin_width_ * -2.f);

    DebugDrawHelper::Get()->DrawBox(bounds.center, bounds.size, Math::Color::Green);
}

void Controller2D::Move(Math::Vector2 velocity)
{
    UpdateRaycastOrigins();
    collisions_.Reset();
    
    if (velocity.x != 0.f) HorizontalCollisions(velocity);
    if (velocity.y != 0.f) VerticalCollisions(velocity);
    
    GetTransform()->Translate(velocity);
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

void Controller2D::HorizontalCollisions(Math::Vector2& velocity)
{
    float dir_x = Math::Sign(velocity.x);
    float ray_length = Math::Abs(velocity.x) + skin_width_;

    for (int i = 0; i < horizontal_ray_count_; ++i)
    {
        Math::Vector2 ray_origin = dir_x == -1 ? raycast_origins_.bottom_left : raycast_origins_.bottom_right;
        ray_origin += Math::Vector2::Up() * (horizontal_ray_spacing_ * i);

        DebugDrawHelper::Get()->DrawRay(ray_origin, Math::Vector2::Right() * dir_x * ray_length, Math::Color::Red);

        HitResult hit_result;
        if (Physics2D::RayCast(hit_result, ray_origin, Math::Vector2::Right() * dir_x, ray_length))
        {
            DebugDrawHelper::Get()->DrawRay(hit_result.point, hit_result.normal, Math::Color::Blue);
            float slope_angle = Math::Vector2::Angle(hit_result.normal, Math::Vector2::Up());
            if (i == 0 && slope_angle <= 80.f)
            {
                float dist_to_slope_start = 0.f;
                if (slope_angle != collisions_.slope_angle_old)
                {
                    dist_to_slope_start = hit_result.distance - skin_width_;
                    velocity.x -= dist_to_slope_start * dir_x;
                }
                
                ClimbSlope(velocity, slope_angle);
                velocity.x += dist_to_slope_start * dir_x;
            }

            if (!collisions_.climbing_slope || slope_angle > 80.f)
            {
                velocity.x = (hit_result.distance - skin_width_) * dir_x;
                ray_length = hit_result.distance;

                if (collisions_.climbing_slope)
                {
                    velocity.y = std::tan(collisions_.slope_angle * (MATH_PI / 180.f)) * Math::Abs(velocity.x);
                }

                collisions_.left = dir_x == -1;
                collisions_.right = dir_x == 1;
            }
        }
    }
}

void Controller2D::VerticalCollisions(Math::Vector2& velocity)
{
    float dir_y = Math::Sign(velocity.y);
    float ray_length = Math::Abs(velocity.y) + skin_width_;
    
    for (int i = 0; i < vertical_ray_count_; ++i)
    {
        Math::Vector2 ray_origin = dir_y == -1 ? raycast_origins_.bottom_left : raycast_origins_.top_left;
        ray_origin += Math::Vector2::Right() * (vertical_ray_spacing_ * i + velocity.x);

        DebugDrawHelper::Get()->DrawRay(ray_origin, Math::Vector2::Up() * dir_y * ray_length, Math::Color::Red);

        HitResult hit_result;
        if (Physics2D::RayCast(hit_result, ray_origin, Math::Vector2::Up() * dir_y, ray_length))
        {
            velocity.y = (hit_result.distance - skin_width_) * dir_y;
            ray_length = hit_result.distance;

            if (collisions_.climbing_slope)
            {
                velocity.x = velocity.y / std::tan(collisions_.slope_angle * (MATH_PI / 180.f)) * Math::Sign(velocity.x);
            }

            collisions_.below = dir_y == -1;
            collisions_.above = dir_y == 1;
        }
    }
}

void Controller2D::ClimbSlope(Math::Vector2& velocity, float slope_angle)
{
    float max_dist = Math::Abs(velocity.x);
    float climb_vel_y = std::sin(slope_angle * (MATH_PI / 180.f)) * max_dist;
    if (velocity.y <= climb_vel_y)
    {
        velocity.y = std::sin(slope_angle * (MATH_PI / 180.f)) * max_dist;
        velocity.x = std::cos(slope_angle * (MATH_PI / 180.f)) * max_dist * Math::Sign(velocity.x);
        collisions_.below = true;
        collisions_.climbing_slope = true;
        collisions_.slope_angle = slope_angle;
    }
}
