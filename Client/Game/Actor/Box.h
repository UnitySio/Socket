#pragma once
#include "../../Engine/Actor/Actor.h"

class Box : public Actor
{
public:
    Box(b2World* world, const std::wstring& kName);
    virtual ~Box() override = default;

private:
    class BoxColliderComponent* box_;
    
};
