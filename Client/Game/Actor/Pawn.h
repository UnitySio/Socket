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
    virtual void Render(float alpha) override;
    virtual void EndPlay(EndPlayReason type) override;

private:
    // Actor components
    class BoxColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;
    class AudioListenerComponent* audio_listener_;
    class SpriteRendererComponent* sprite_renderer_;
};