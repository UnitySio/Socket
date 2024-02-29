#pragma once
#include "box2d/b2_math.h"
#include "box2d/b2_world_callbacks.h"

class QueryCallback : public b2QueryCallback
{
public:
    QueryCallback(const b2Vec2& kPoint);
    virtual ~QueryCallback() override = default;
    
    bool ReportFixture(b2Fixture* fixture) override;

    inline b2Vec2 GetPoint() const { return point_; }
    inline b2Fixture* GetFixture() const { return fixture_; }

private:
    b2Vec2 point_;
    class b2Fixture* fixture_;
    
};
