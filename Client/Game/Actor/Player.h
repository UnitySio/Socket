#pragma once
#include "../../Engine/Actor/Actor.h"

#include "box2d/b2_draw.h"
#include "box2d/b2_world_callbacks.h"

class Player : public Actor, public b2RayCastCallback
{
public:
    Player(class b2World* world);
    virtual ~Player() final = default;

    virtual float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) final;
    
    virtual void Begin() final;
    virtual void Tick(float deltaTime) final;
    virtual void Render() final;
    virtual void OnCollisionBegin(Actor* other) final;
    virtual void OnCollisionEnd(Actor* other) final;

private:
    b2Color color_;

    bool is_ground_;
    
};
