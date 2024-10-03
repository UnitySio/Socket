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

class RayCastController : public ActorComponent
{
public:
    RayCastController(Actor* owner, const std::wstring& kName);
    virtual ~RayCastController() override = default;

    virtual void BeginPlay() override;
    
    inline void SetCollider(class ColliderComponent* collider) { collider_ = collider; }

protected:
    void UpdateRaycastOrigins();
    void CalculateRaySpecing();
    
    class ColliderComponent* collider_;
    
    float skin_width_;
    float horizontal_ray_spacing_;
    float vertical_ray_spacing_;
    
    int horizontal_ray_count_;
    int vertical_ray_count_;
    
    RaycastOrigins raycast_origins_;

    RTTR_ENABLE(ActorComponent)
    RTTR_REGISTRATION_FRIEND
    
};
