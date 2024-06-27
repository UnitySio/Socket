#pragma once
#include "Actor/Actor.h"

class BoxColliderComponent;

class CharacterBase : public Actor
{
public:
    CharacterBase(const std::wstring& kName);
    virtual ~CharacterBase() override = default;

    inline BoxColliderComponent* GetBoxCollider() const { return box_collider_; }
    inline RigidBodyComponent* GetRigidBody() const { return rigid_body_; }

protected:
    BoxColliderComponent* box_collider_;
    RigidBodyComponent* rigid_body_;
    
};
