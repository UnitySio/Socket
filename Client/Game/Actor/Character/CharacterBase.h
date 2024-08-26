#pragma once
#include "Actor/Actor.h"
#include "Actor/StateMachine/StateMachine.h"

class SpriteRendererComponent;
class AnimatorComponent;
class CapsuleColliderComponent;
class RigidBodyComponent;

class CharacterBase : public StateMachine
{
    SHADER_CLASS_HELPER(CharacterBase)
    
public:
    CharacterBase(const std::wstring& kName);
    virtual ~CharacterBase() override = default;

    inline SpriteRendererComponent* GetSpriteRenderer() const { return sprite_renderer_; }
    inline AnimatorComponent* GetAnimator() const { return animator_; }
    inline CapsuleColliderComponent* GetCapsuleCollider() const { return capsule_collider_; }
    inline RigidBodyComponent* GetRigidBody() const { return rigid_body_; }

protected:
    SpriteRendererComponent* sprite_renderer_;
    AnimatorComponent* animator_;
    CapsuleColliderComponent* capsule_collider_;
    RigidBodyComponent* rigid_body_;
    
};
