#pragma once
#include <vector>

#include "box2d/b2_world_callbacks.h"

class Actor;

class HitResult : public b2RayCastCallback
{
public:
    HitResult();
    
    // RayCast
    virtual float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) final;

    inline std::vector<Actor*> GetActors() const { return actors_; }

private:
    std::vector<Actor*> actors_;
    
};
