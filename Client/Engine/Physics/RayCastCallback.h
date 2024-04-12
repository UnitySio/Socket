#pragma once

#include "HitResult.h"
#include "box2d/b2_world_callbacks.h"

class RayCastCallback : public b2RayCastCallback
{
public:
    RayCastCallback();
    virtual ~RayCastCallback() override = default;
    
    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;

    inline bool IsHit() const { return is_hit_; }
    
    inline HitResult GetHitResult() const { return hit_result_; }

private:
    bool is_hit_;

    HitResult hit_result_;
    
};
