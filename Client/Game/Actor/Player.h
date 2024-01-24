#pragma once
#include "../../Engine/Actor/Actor.h"

#include "box2d/b2_draw.h"

class Player : public Actor
{
public:
    Player(class b2World* world);
    virtual ~Player() = default;
    
    virtual void Begin() final;
    virtual void Tick(float deltaTime) final;
    virtual void Render() final;
    virtual void OnCollisionBegin(Actor* other) final;
    virtual void OnCollisionEnd(Actor* other) final;

private:
    b2Color color_;

    bool is_focused_;
    
};
