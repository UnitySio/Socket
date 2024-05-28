#pragma once
#include "Actor/Actor.h"

class Sprite;

class Pawn : public Actor
{
public:
    Pawn(const std::wstring& kName);
    virtual ~Pawn() override = default;

    virtual void BeginPlay() override;
    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;
    virtual void Render(float alpha) override;
    virtual void EndPlay(EndPlayReason type) override;

private:
    // Actor components
    class InputComponent* input_;
    class BoxColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;
    class AudioListenerComponent* audio_listener_;

    SHARED_PTR<Sprite> sprite_;

    // TEST
    float timer;
    MathTypes::uint32 frame_index;
    
};
