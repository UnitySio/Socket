#pragma once
#include "../../Engine/Actor/Actor.h"
#include "Graphics/Sprite.h"

class Pawn : public Actor
{
public:
    Pawn(const std::wstring& kName);
    virtual ~Pawn() override = default;

    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;
    virtual void Render() override;
    virtual void EndPlay(EndPlayReason type) override;

private:
    // Actor components
    class BoxColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;
    class AudioListenerComponent* audio_listener_;

    std::unique_ptr<Sprite> sprite_;

    int dir_;
    
};
