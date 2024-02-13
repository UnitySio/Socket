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
    class BoxComponent* box_;
    class CameraComponent* camera_view_;
    
};
