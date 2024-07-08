#pragma once
#include "Actor/Actor.h"

class AnimatorComponent;
class SpriteRendererComponent;
class BoxColliderComponent;

class CharacterBase : public Actor
{
public:
    CharacterBase(const std::wstring& kName);
    virtual ~CharacterBase() override = default;

    inline SpriteRendererComponent* GetSpriteRenderer() const { return sprite_renderer_; }
    inline BoxColliderComponent* GetBoxCollider() const { return box_collider_; }
    inline RigidBodyComponent* GetRigidBody() const { return rigid_body_; }

protected:
    SpriteRendererComponent* sprite_renderer_;
    AnimatorComponent* animator_;
    BoxColliderComponent* box_collider_;
    RigidBodyComponent* rigid_body_;
    
};
