﻿#pragma once
#include "Actor/Actor.h"

class Pawn : public Actor
{
public:
    Pawn(World* world, const std::wstring& kName);
    virtual ~Pawn() override = default;

    virtual void BeginPlay() override;
    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;
    virtual void Render(float alpha) override;
    virtual void EndPlay(EndPlayReason type) override;

    void OnCallback();

private:
    // Actor components
    class InputComponent* input_;
    class BoxColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;
    class AudioListenerComponent* audio_listener_;
    
};
