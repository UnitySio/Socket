#pragma once
#include "../../Engine/Actor/Actor.h"

#include "box2d/b2_draw.h"
#include "box2d/b2_world_callbacks.h"

class Player : public Actor
{
public:
    Player(class b2World* world);
    virtual ~Player() final = default;

    virtual void Begin() final;
    virtual void Tick(float deltaTime) final;
    virtual void Render() final;

private:
    bool is_ground_;
    
};
