#pragma once
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
    virtual void Render() override;

private:
    // Scene components
    class SceneComponent* scene_;

    // Actor components
    class BoxColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;

    class b2Body* body_;
    class b2MouseJoint* mouse_joint_;

    int dir_;
    
    class ID2D1Bitmap* bitmap_;
    class SpriteComponent* sprite_;
    class AnimationComponent* animation_;
};
