#pragma once
#include "../../Engine/Actor/Actor.h"

class Floor : public Actor
{
public:
    Floor(b2World* world, const std::wstring& kName);
    virtual ~Floor() override = default;

private:
    class BoxColliderComponent* box_collider_;
    
};
