#pragma once
#include "../../Engine/Actor/Actor.h"

class Pawn : public Actor
{
public:
    Pawn(b2World* world, const std::wstring& kName);
    virtual ~Pawn() override = default;

    virtual void Tick(float delta_time) override;
    virtual void Render() override;

private:
    class BoxComponent* box_;
    class CircleComponent* circle_;
    class SpriteComponent* sprite_;
    class CameraComponent* camera_view_;

    class ID2D1Bitmap* bitmap_;
    
};
