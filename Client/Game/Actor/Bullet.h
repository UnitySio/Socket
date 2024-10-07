#pragma once
#include "Actor/Actor.h"

class Bullet : public Actor
{
    SHADER_CLASS_HELPER(Bullet)
    GENERATED_BODY(Bullet, Actor)
    
public:
    Bullet(const std::wstring& kName);
    virtual ~Bullet() override = default;

    virtual void BeginPlay() override;
    virtual void OnEnable() override;

    void Pop();
    void Push();

private:
    class CircleColliderComponent* circle_collider_;
    class RigidBody2DComponent* rigid_body_;
    
};
