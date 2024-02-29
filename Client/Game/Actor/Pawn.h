﻿#pragma once
#include "../../Engine/Bounds.h"
#include "../../Engine/Actor/Actor.h"

class Pawn : public Actor
{
public:
    Pawn(b2World* world, const std::wstring& kName);
    virtual ~Pawn() override = default;

    virtual void BeginPlay() override;
    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;

private:
    // Scene components
    class CameraComponent* camera_view_;

    // Actor components
    class BoxColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;

    class b2Body* body_;
    class b2MouseJoint* mouse_joint_;
    
};
