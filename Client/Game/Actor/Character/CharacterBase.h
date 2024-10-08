﻿#pragma once
#include "Actor/Actor.h"
#include "Actor/Component/CapsuleColliderComponent.h"
#include "Actor/StateMachine/StateMachine.h"

class AnimatorComponent;
class Controller2DComponent;
class SpriteRendererComponent;

class CharacterBase : public Actor
{
    SHADER_CLASS_HELPER(CharacterBase)
    GENERATED_BODY(CharacterBase, Actor)
    
public:
    CharacterBase(const std::wstring& kName);
    virtual ~CharacterBase() override = default;

    virtual class ColliderComponent* GetCollider() override { return capsule_collider_; }

    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;
    virtual void PostTick(float delta_time) override;

    inline SpriteRendererComponent* GetSpriteRenderer() const { return sprite_renderer_; }
    inline AnimatorComponent* GetAnimator() const { return animator_; }
    inline Controller2DComponent* GetController() const { return controller_; }

protected:
    std::unique_ptr<StateMachine> state_machine_;
    
    SpriteRendererComponent* sprite_renderer_;
    AnimatorComponent* animator_;
    class CapsuleColliderComponent* capsule_collider_;
    Controller2DComponent* controller_;
    
};
