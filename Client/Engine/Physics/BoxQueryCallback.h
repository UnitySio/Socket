#pragma once
#include <vector>

#include "box2d/b2_world_callbacks.h"
#include "Math/MathTypes.h"

class Actor;

class BoxQueryCallback : public b2QueryCallback
{
public:
    BoxQueryCallback(bool is_single, MathTypes::uint16 layer);
    virtual ~BoxQueryCallback() override = default;
    
    virtual bool ReportFixture(b2Fixture* fixture) override;

    inline const std::vector<Actor*>& GetActors() const { return actors_; }

private:
    bool is_single_;
    MathTypes::uint16 layer_;
    
    std::vector<Actor*> actors_;
    
};
