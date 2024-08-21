#pragma once
#include "Actor/Actor.h"

class Box : public Actor
{
    DECLARE_SHARED_CLASS(Actor, Box)
    
public:
    Box(const std::wstring& kName);
    virtual ~Box() override = default;

    virtual void BeginPlay() override;

private:
    class SpriteRendererComponent* sprite_renderer_;
    class BoxColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;
    
    std::shared_ptr<class Sprite> sprite_;
    
};
