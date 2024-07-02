#pragma once
#include "Actor/Actor.h"

class Box : public Actor
{
public:
    Box(const std::wstring& kName);
    virtual ~Box() override = default;

    virtual void Render(float alpha) override;

private:
    class BoxColliderComponent* box_collider_;
    class RigidBodyComponent* rigid_body_;
    
    SHARED_PTR<class Sprite> sprite_;
    
};
