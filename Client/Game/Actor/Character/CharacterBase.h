#pragma once
#include "Actor/Actor.h"
#include "Actor/Component/CapsuleColliderComponent.h"
#include "Math/Vector2.h"

class CharacterBase : public Actor
{
    SHADER_CLASS_HELPER(CharacterBase)
    
public:
    CharacterBase(const std::wstring& kName);
    virtual ~CharacterBase() override = default;

    virtual class ColliderComponent* GetCollider() override { return capsule_collider_; }
    virtual void Tick(float delta_time) override;

protected:
    std::shared_ptr<class StateMachine> state_machine_;
    
    class SpriteRendererComponent* sprite_renderer_;
    class CapsuleColliderComponent* capsule_collider_;
    class Controller2DComponent* controller_;

    Math::Vector2 velocity_;

    float gravity_;
    
};
