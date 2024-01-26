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
    b2Vec2 GetScreenToWorldPosition(b2Vec2 position);

    inline b2Vec2 GetScreenPosition() const { return screen_position_; }

    inline void SetTarget(Actor* target) { target_ = target; }

private:
    b2Vec2 Lerp(b2Vec2 a, b2Vec2 b, float t);
    
    static Camera* instance_;
    
    b2Vec2 screen_position_;

    Actor* target_;
    
};
