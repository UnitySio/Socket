#pragma once
#include "Controller2D.h"
#include "Actor/Component/CapsuleColliderComponent.h"

class Dummy : public Controller2D
{
    SHADER_CLASS_HELPER(Dummy)
    
public:
    Dummy(const std::wstring& kName);
    virtual ~Dummy() override = default;

    virtual void BeginPlay() override;
    virtual void Tick(float delta_time) override;

    inline virtual class CapsuleColliderComponent* GetCollider() override { return capsule_collider_; }

private:
    float gravity_;
    float jump_height_;
    float time_to_jump_apex_;
    float jump_velocity_;
    float move_speed_;
    
    Math::Vector2 velocity_;
    
};
