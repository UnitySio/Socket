#pragma once
#include "Actor/Actor.h"

class Floor : public Actor
{
public:
    Floor(b2World* world, const std::wstring& kName);
    virtual ~Floor() override = default;

    class BoxColliderComponent* GetBoxCollider() const { return box_collider_; }

private:
    class BoxColliderComponent* box_collider_;
    
};
