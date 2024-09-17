#pragma once
#include "Actor/Component/ActorComponent.h"
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

class Controller2DComponent : public ActorComponent
{
    SHADER_CLASS_HELPER(Controller2DComponent)
    
public:
    Controller2DComponent(class Actor* owner, const std::wstring& kName);
    virtual ~Controller2DComponent() override = default;

    virtual void BeginPlay() override;
    
    void Move(Math::Vector2 velocity);

    inline void SetCollider(class ColliderComponent* collider) { collider_ = collider; }

    inline const CollisionInfo& GetCollisions() const { return collisions_; }
    inline bool IsGrounded() const { return collisions_.below; }

private:
    void UpdateRaycastOrigins();
    void CalculateRaySpecing();
    void HorizontalCollisions(Math::Vector2& velocity);
    void VerticalCollisions(Math::Vector2& velocity);
    void ClimbSlope(Math::Vector2& velocity, float slope_angle);
    void DescendSlope(Math::Vector2& velocity);
    
    class ColliderComponent* collider_;

    float skin_width_;

    int horizontal_ray_count_;
    int vertical_ray_count_;

    float horizontal_ray_spacing_;
    float vertical_ray_spacing_;

    RaycastOrigins raycast_origins_;
    CollisionInfo collisions_;
    
};
