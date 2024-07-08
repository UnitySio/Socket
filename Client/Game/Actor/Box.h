#pragma once
#include "Actor/Actor.h"

class Box : public Actor
{
public:
    Box(const std::wstring& kName);
    virtual ~Box() override = default;

private:
    class SpriteRendererComponent* sprite_renderer_;
    class BoxColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;
    
    SHARED_PTR<class Sprite> sprite_;
    
};
