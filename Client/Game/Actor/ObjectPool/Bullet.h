﻿#pragma once
#include "PooledObject.h"

class Bullet : public PooledObject
{
    SHADER_CLASS_HELPER(Bullet)
    GENERATED_BODY(Bullet, PooledObject)
    
public:
    Bullet(const std::wstring& kName);
    virtual ~Bullet() override = default;

    virtual void OnEnable() override;

private:
    class CircleColliderComponent* circle_collider_;
    class RigidBody2DComponent* rigid_body_;
    class SpriteRendererComponent* sprite_renderer_;

    class Sprite* sprite_;
    
};
