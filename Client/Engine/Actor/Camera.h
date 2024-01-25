#pragma once
#include "Actor.h"
#include "box2d/b2_math.h"

class Camera : public Actor
{
public:
    Camera(b2World* world);
    virtual ~Camera() final = default;

    virtual void Tick(float deltaTime) final;

    static Camera* GetInstance() { return instance_; }

    b2Vec2 GetRenderPosition(b2Vec2 position);

private:
    static Camera* instance_;
    
    b2Vec2 screen_position_;
    
};
