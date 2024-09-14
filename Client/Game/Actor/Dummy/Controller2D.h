#pragma once
#include "Actor/Actor.h"
#include "Math/Vector2.h"

struct RaycastOrigins
{
    Math::Vector2 bottom_left;
    Math::Vector2 bottom_right;
    Math::Vector2 top_left;
    Math::Vector2 top_right;
};

struct CollisionInfo
{
    bool above;
    bool below;
    bool left;
    bool right;
    bool climbing_slope;
    bool descending_slope;

    float slope_angle;
    float slope_angle_old;

    Math::Vector2 velocity_old;

    void Reset()
    {
        above = false;
        below = false;
        left = false;
        right = false;
        climbing_slope = false;
        descending_slope = false;

        slope_angle_old = slope_angle;
        slope_angle = 0;
    }
};

class Controller2D : public Actor
{
    SHADER_CLASS_HELPER(Controller2D)
    
public:
    Controller2D(const std::wstring& kName);
    virtual ~Controller2D() override = default;

    virtual void BeginPlay() override;
    virtual void Tick(float delta_time) override;
    
    void Move(Math::Vector2 velocity);

protected:
    void UpdateRaycastOrigins();
    void CalculateRaySpecing();
    void HorizontalCollisions(Math::Vector2& velocity);
    void VerticalCollisions(Math::Vector2& velocity);
    void ClimbSlope(Math::Vector2& velocity, float slope_angle);
    void DescendSlope(Math::Vector2& velocity);
    
    class CapsuleColliderComponent* capsule_collider_;

    float skin_width_;

    int horizontal_ray_count_;
    int vertical_ray_count_;

    float horizontal_ray_spacing_;
    float vertical_ray_spacing_;

    RaycastOrigins raycast_origins_;
    CollisionInfo collisions_;
    
};
