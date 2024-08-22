#pragma once
#include "Actor/Actor.h"

class Box : public Actor
{
    SHADER_CLASS_HELPER(Box)
    
public:
    Box(const std::wstring& kName);
    virtual ~Box() override = default;

    virtual void BeginPlay() override;
    virtual void Tick(float delta_time) override;

private:
    class SpriteRendererComponent* sprite_renderer_;
    class BoxColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;
    
    std::shared_ptr<class Sprite> sprite_;
    
};
