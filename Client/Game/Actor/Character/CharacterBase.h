#pragma once
#include "Actor/Actor.h"
#include "Actor/Component/CapsuleColliderComponent.h"
#include "Actor/StateMachine/StateMachine.h"

class SpriteRendererComponent;
class AnimatorComponent;
class RigidBody2DComponent;

class CharacterBase : public StateMachine
{
    SHADER_CLASS_HELPER(CharacterBase)
    
public:
    CharacterBase(const std::wstring& kName);
    virtual ~CharacterBase() override = default;

    virtual void Tick(float delta_time) override;

    void Jump();

    bool CanJump() const;

    inline virtual class ColliderComponent* GetCollider() override { return capsule_collider_; }

    inline SpriteRendererComponent* GetSpriteRenderer() const { return sprite_renderer_; }
    inline AnimatorComponent* GetAnimator() const { return animator_; }
    inline CapsuleColliderComponent* GetCapsuleCollider() const { return capsule_collider_; }
    inline RigidBody2DComponent* GetRigidBody() const { return rigid_body_; }

protected:
    SpriteRendererComponent* sprite_renderer_;
    AnimatorComponent* animator_;
    CapsuleColliderComponent* capsule_collider_;
    RigidBody2DComponent* rigid_body_;

    bool is_jumping_;
    bool is_falling_;

    Math::Vector2 ground_check_size_;

    float last_on_ground_time_;
    float coyote_time_;
    float jump_force_;
    float gravity_scale_;
    float fall_gravity_multiplier_;
    float max_fall_speed_;
    
};
