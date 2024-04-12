#pragma once
#include "box2d/b2_world_callbacks.h"
#include "Math/Vector.h"

class Actor;

class RayCastCallback : public b2RayCastCallback
{
public:
    RayCastCallback();
    virtual ~RayCastCallback() override = default;
    
    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;

    inline bool IsHit() const { return is_hit_; }

    inline const Vector& GetLocation() const { return location_; }
    inline const Vector& GetNormal() const { return normal_; }

    inline Actor* GetActor() const { return actor_; }

private:
    bool is_hit_;

    Vector location_;
    Vector normal_;
    
    Actor* actor_;
    
};
