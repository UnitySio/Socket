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

class Controller2D : public Actor
{
    SHADER_CLASS_HELPER(Controller2D)
    
public:
    Controller2D(const std::wstring& kName);
    virtual ~Controller2D() override = default;

    virtual void Tick(float delta_time) override;

protected:
    void UpdateRaycastOrigins();
    void CalculateRaySpecing();
    
    class BoxColliderComponent* box_collider_;

    float skin_width_;

    int horizontal_ray_count_;
    int vertical_ray_count_;

    float horizontal_ray_spacing_;
    float vertical_ray_spacing_;

    RaycastOrigins raycast_origins_;
    
};
