#pragma once
#include "Actor/Actor.h"
#include "Actor/Component/CapsuleColliderComponent.h"
#include "Actor/StateMachine/StateMachine.h"
#include "Math/Vector2.h"

class Controller2DComponent;
class SpriteRendererComponent;

class CharacterBase : public Actor
{
    SHADER_CLASS_HELPER(CharacterBase)
    
public:
    CharacterBase(const std::wstring& kName);
    virtual ~CharacterBase() override = default;

    virtual class ColliderComponent* GetCollider() override { return capsule_collider_; }
    virtual void Tick(float delta_time) override;

    inline SpriteRendererComponent* GetSpriteRenderer() const { return sprite_renderer_; }
    inline Controller2DComponent* GetController() const { return controller_; }

    inline void SetVelocity(const Math::Vector2& velocity) { velocity_ = velocity; }
    inline Math::Vector2 GetVelocity() const { return velocity_; }

protected:
    std::unique_ptr<StateMachine> state_machine_;
    
    SpriteRendererComponent* sprite_renderer_;
    class CapsuleColliderComponent* capsule_collider_;
    Controller2DComponent* controller_;

    Math::Vector2 velocity_;

    float gravity_;
    
};
