#include "pch.h"
#include "Controller2DComponent.h"

#include "DebugDrawHelper.h"
#include "Actor/Actor.h"
#include "Actor/Component/ColliderComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Math/Bounds.h"
#include "Math/Math.h"
#include "Physics/Physics2D.h"

Controller2DComponent::Controller2DComponent(class Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    skin_width_(.015f),
    slope_limit_(80.f),
    collider_(nullptr),
    horizontal_ray_count_(4),
    vertical_ray_count_(4),
    horizontal_ray_spacing_(0.f),
    vertical_ray_spacing_(0.f),
    raycast_origins_(),
    collisions_()
{
}

void Controller2DComponent::BeginPlay()
{
    ActorComponent::BeginPlay();

    CalculateRaySpecing();
}

void Controller2DComponent::Move(Math::Vector2 velocity)
{
    UpdateRaycastOrigins();
    collisions_.Reset();
    collisions_.velocity_old = velocity;

    if (velocity.y < 0.f) DescendSlope(velocity);
    if (velocity.x != 0.f) HorizontalCollisions(velocity);
    if (velocity.y != 0.f) VerticalCollisions(velocity);
    
    GetOwner()->GetTransform()->Translate(velocity);
}

void Controller2DComponent::UpdateRaycastOrigins()
{
    Bounds bounds = collider_->GetBounds();
    bounds.Expand(skin_width_ * -2.f);

    raycast_origins_.bottom_left = bounds.min;
    raycast_origins_.bottom_right = {bounds.max.x, bounds.min.y};
    raycast_origins_.top_left = {bounds.min.x, bounds.max.y};
    raycast_origins_.top_right = bounds.max;
}

void Controller2DComponent::CalculateRaySpecing()
{
    Bounds bounds = collider_->GetBounds();
    bounds.Expand(skin_width_ * -2.f);

    horizontal_ray_count_ = Math::Clamp(horizontal_ray_count_, 2, 1024);
    horizontal_ray_count_ = Math::Clamp(horizontal_ray_count_, 2, 1024);

    horizontal_ray_spacing_ = bounds.size.y / (horizontal_ray_count_ - 1);
    vertical_ray_spacing_ = bounds.size.x / (vertical_ray_count_ - 1);
}

void Controller2DComponent::HorizontalCollisions(Math::Vector2& velocity)
{
    float dir_x = Math::Sign(velocity.x);
    float ray_length = Math::Abs(velocity.x) + skin_width_;

    for (int i = 0; i < horizontal_ray_count_; ++i)
    {
        Math::Vector2 ray_origin = dir_x == -1 ? raycast_origins_.bottom_left : raycast_origins_.bottom_right;
        ray_origin += Math::Vector2::Up() * (horizontal_ray_spacing_ * i);

        HitResult hit_result;
        if (Physics2D::RayCast(hit_result, ray_origin, Math::Vector2::Right() * dir_x, ray_length, ActorLayer::kGround))
        {
            float slope_angle = Math::Vector2::Angle(hit_result.normal, Math::Vector2::Up());
            if (i == 0 && slope_angle <= slope_limit_)
            {
                if (collisions_.descending_slope)
                {
                    collisions_.descending_slope = false;
                    velocity = collisions_.velocity_old;
                }
                
                float dist_to_slope_start = 0.f;
                if (slope_angle != collisions_.slope_angle_old)
                {
                    dist_to_slope_start = hit_result.distance - skin_width_;
                    velocity.x -= dist_to_slope_start * dir_x;
                }
                
                ClimbSlope(velocity, slope_angle);
                velocity.x += dist_to_slope_start * dir_x;
            }

            if (!collisions_.climbing_slope || slope_angle > slope_limit_)
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

void Controller2DComponent::VerticalCollisions(Math::Vector2& velocity)
{
    float dir_y = Math::Sign(velocity.y);
    float ray_length = Math::Abs(velocity.y) + skin_width_;
    
    for (int i = 0; i < vertical_ray_count_; ++i)
    {
        Math::Vector2 ray_origin = dir_y == -1 ? raycast_origins_.bottom_left : raycast_origins_.top_left;
        ray_origin += Math::Vector2::Right() * (vertical_ray_spacing_ * i + velocity.x);

        HitResult hit_result;
        if (Physics2D::RayCast(hit_result, ray_origin, Math::Vector2::Up() * dir_y, ray_length, ActorLayer::kGround))
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

    if (collisions_.climbing_slope)
    {
        float dir_x = Math::Sign(velocity.x);
        ray_length = Math::Abs(velocity.x) + skin_width_;
        Math::Vector2 ray_origin = (dir_x == -1 ? raycast_origins_.bottom_left : raycast_origins_.bottom_right) + Math::Vector2::Up() * velocity.y;

        HitResult hit_result;
        if (Physics2D::RayCast(hit_result, ray_origin, Math::Vector2::Right() * dir_x, ray_length, ActorLayer::kGround))
        {
            float slope_angle = Math::Vector2::Angle(hit_result.normal, Math::Vector2::Up());
            if (slope_angle != collisions_.slope_angle)
            {
                velocity.x = (hit_result.distance - skin_width_) * dir_x;
                collisions_.slope_angle = slope_angle;
            }
        }
    }
}

void Controller2DComponent::ClimbSlope(Math::Vector2& velocity, float slope_angle)
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

void Controller2DComponent::DescendSlope(Math::Vector2& velocity)
{
    float dir_x = Math::Sign(velocity.x);
    Math::Vector2 ray_origin = dir_x == -1 ? raycast_origins_.bottom_right : raycast_origins_.bottom_left;

    HitResult hit_result;
    if (Physics2D::RayCast(hit_result, ray_origin, Math::Vector2::Down(), std::numeric_limits<float>::max(), ActorLayer::kGround))
    {
        float slope_angle = Math::Vector2::Angle(hit_result.normal, Math::Vector2::Up());
        
        if (slope_angle != 0.f && slope_angle <= slope_limit_)
        {
            if (Math::Sign(hit_result.normal.x) == dir_x)
            {
                if (hit_result.distance - skin_width_ <= std::tan(slope_angle * (MATH_PI / 180.f)) * Math::Abs(velocity.x))
                {
                    float move_distance = Math::Abs(velocity.x);
                    float descend_vel_y = std::sin(slope_angle * (MATH_PI / 180.f)) * move_distance;
                    velocity.x = std::cos(slope_angle * (MATH_PI / 180.f)) * move_distance * Math::Sign(velocity.x);
                    velocity.y -= descend_vel_y;

                    collisions_.slope_angle = slope_angle;
                    collisions_.descending_slope = true;
                    collisions_.below = true;
                }
            }
        }
    }
}
