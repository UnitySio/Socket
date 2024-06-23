#pragma once
#include "Actor/Actor.h"
#include "Misc/Delegate.h"
#include "Time/TimerManager.h"

class BoxColliderComponent;
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

    BoxColliderComponent* GetBoxCollider() const { return box_collider_; }

private:
    // Actor components
    class InputComponent* input_;
    BoxColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;
    class AudioListenerComponent* audio_listener_;

    SHARED_PTR<Sprite> sprite_;

    char dir_;

    // TEST
    float timer_;
    MathTypes::uint32 frame_index_;

};

