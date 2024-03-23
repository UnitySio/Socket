#pragma once
#include "../../Engine/Actor/Actor.h"
#include "Graphics/Sprite.h"

class Pawn : public Actor
{
public:
    Pawn(b2World* world, const std::wstring& kName);
    virtual ~Pawn() override = default;

    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;
    virtual void Render() override;

private:
    // Scene components
    class SceneComponent* scene_;

    // Actor components
    class BoxColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;

    std::unique_ptr<Sprite> sprite_;

    int dir_;
};
