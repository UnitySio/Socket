#pragma once
#include "Actor/Actor.h"

class Dummy : public Actor
{
public:
    Dummy(b2World* world, const std::wstring& kName);
    virtual ~Dummy() override = default;

    inline class BoxColliderComponent* GetBoxCollider() const { return box_collider_; }
    inline class RigidBodyComponent* GetRigidBody() const { return rigid_body_; }

private:
    class BoxColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;
    
};
