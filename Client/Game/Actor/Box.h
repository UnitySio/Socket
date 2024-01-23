#pragma once
#include "../../Engine/Actor/Actor.h"

class Box : public Actor
{
public:
    Box(b2World* world);
    virtual ~Box() = default;
    
    virtual void Begin() final;
    virtual void Tick(float deltaTime) final;
    virtual void Render() final;
    
};
