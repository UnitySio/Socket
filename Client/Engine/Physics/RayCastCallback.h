﻿#pragma once
#include <vector>

#include "RayCastResult.h"
#include "box2d/b2_world_callbacks.h"
#include "Math/MathTypes.h"

class RayCastCallback : public b2RayCastCallback
{
public:
    RayCastCallback(bool is_single, MathTypes::uint16 layer);
    virtual ~RayCastCallback() override = default;
    
    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;

    inline const std::vector<RayCastResult>& GetResults() const { return results_; }

private:
    bool is_single_;
    MathTypes::uint16 layer_;
    
    std::vector<RayCastResult> results_;
    
};
