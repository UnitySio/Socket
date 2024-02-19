#pragma once
#include "../../Engine/Actor/Actor.h"

class Dummy : public Actor
{
public:
    Dummy(b2World* world, const std::wstring& kName);
    virtual ~Dummy() override = default;

    inline class BoxColliderComponent* GetBoxCollider() const { return box_collider_; }

private:
    class BoxColliderComponent* box_collider_;
    
};
