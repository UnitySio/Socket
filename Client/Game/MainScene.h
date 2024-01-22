#pragma once
#include "../Engine/Scene/Scene.h"
#include "box2d/b2_math.h"
#include "box2d/b2_world.h"

class MainScene : public Scene
{
public:
    MainScene();
    virtual ~MainScene() final = default;

    virtual void Begin() final;
    virtual void End() final;
    virtual void Tick(float deltaTime) final;
    virtual void Render() final;

private:
    b2Vec2 gravity_;
    b2World world_;

    b2Body* ground_body_;
    b2Body* dynamic_body_;
    
};
