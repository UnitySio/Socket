#pragma once
#include "Actor/Actor.h"

class Box : public Actor
{
public:
    Box(const std::wstring& kName);
    virtual ~Box() override = default;

private:
    class CircleColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;
    
};
