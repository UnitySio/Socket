#pragma once
#include "../../Engine/Actor/Actor.h"

class Player : public Actor
{
public:
    Player(class b2World* world);
    virtual ~Player() override = default;

    virtual void Begin() override;
    virtual void Tick(float deltaTime) override;
    virtual void Render() override;

private:
    bool is_ground_;
    
};
