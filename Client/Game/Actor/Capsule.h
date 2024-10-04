#pragma once
#include "Actor/Actor.h"

class Capsule : public Actor
{
    SHADER_CLASS_HELPER(Capsule)
    GENERATED_BODY(Capsule, Actor)
    
public:
    Capsule(const std::wstring& kName);
    virtual ~Capsule() override = default;

    virtual void BeginPlay() override;
    virtual void Tick(float delta_time) override;

private:
    class SpriteRendererComponent* sprite_renderer_;
    class CapsuleColliderComponent* capsule_collider_;
    class RigidBody2DComponent* rigid_body_;
    
    class Sprite* sprite_;
    
};
