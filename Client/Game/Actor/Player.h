#pragma once
#include "../../Engine/Actor/Actor.h"

class Player : public Actor
{
public:
    Player(class b2World* world);
    virtual ~Player() = default;
    
    virtual void Begin() final;
    virtual void Tick(float deltaTime) final;
    virtual void Render() final;
    
};
