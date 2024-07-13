#pragma once
#include <vector>

#include "box2d/b2_math.h"
#include "box2d/b2_world_callbacks.h"
#include "Math/MathTypes.h"

class Actor;

class CircleQueryCallback : public b2QueryCallback
{
public:
    CircleQueryCallback(bool is_single_, const b2Vec2& center, float radius, MathTypes::uint16 layer);
    virtual ~CircleQueryCallback() override = default;
    
    virtual bool ReportFixture(b2Fixture* fixture) override;

    inline const std::vector<Actor*>& GetActors() const { return actors_; }

private:
    bool is_single_;
    b2Vec2 center_;
    float radius_;
    MathTypes::uint16 layer_;
    
    std::vector<Actor*> actors_;
    
};
