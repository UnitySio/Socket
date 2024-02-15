#pragma once
#include "../../Engine/Actor/Actor.h"

class Pawn : public Actor
{
public:
    Pawn(b2World* world, const std::wstring& kName);
    virtual ~Pawn() override = default;

    virtual void BeginPlay() override;
    virtual void Tick(float delta_time) override;

private:
    // Scene components
    class BoxColliderComponent* box_;
    class CameraComponent* camera_view_;

    // Actor components
    class RigidBodyComponent* rigid_body_;
    
};
