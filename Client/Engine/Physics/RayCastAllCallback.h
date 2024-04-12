#pragma once
#include <vector>

#include "box2d/b2_world_callbacks.h"

struct HitResult;

class RayCastAllCallback : public b2RayCastCallback
{
public:
    RayCastAllCallback();
    virtual ~RayCastAllCallback() override = default;
    
    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;

    inline const std::vector<HitResult>& GetHitResults() const { return hit_results_; }

private:
    std::vector<HitResult> hit_results_;
    
};
