#pragma once
#include "ActorComponent.h"
#include "box2d/b2_body.h"

namespace Math
{
    struct Vector2;
}

enum class BodyType : size_t
{
    kDynamic = 0,
    kKinematic,
    kStatic
};

enum class SleepMode : size_t
{
    kNeverSleep = 0,
    kStartAwake
};

enum class CollisionDetectionMode : size_t
{
    kDiscrete = 0,
    kContinuous
};

enum class ForceMode : size_t
{
    kForce = 0,
    kImpulse
};

class RigidBodyComponent : public ActorComponent
{
    DECLARE_SHARED_CLASS(ActorComponent, RigidBodyComponent)
    
public:
    RigidBodyComponent(class Actor* owner, const std::wstring& kName);
    virtual ~RigidBodyComponent() override = default;

    void SetBodyType(BodyType type);
    void SetGravityScale(float scale);
    void SetSleepMode(SleepMode mode);
    void SetCollisionDetectionMode(CollisionDetectionMode mode);
    void SetFreezeRotation(bool freeze);
    void SetVelocity(const Math::Vector2& kVelocity);
    void SetAngularVelocity(float velocity);
    void AddForce(const Math::Vector2& kForce, ForceMode mode = ForceMode::kForce);
    void AddForceAtPosition(const Math::Vector2& kForce, const Math::Vector2& kPosition, ForceMode mode = ForceMode::kForce);
    void AddTorque(float torque, ForceMode mode = ForceMode::kForce);
    void Sleep();
    void WakeUp();

    Math::Vector2 GetVelocity() const;
    
    float GetAngularVelocity() const;

    bool IsAwake() const;

    b2BodyType GetBodyType() const;
    
};
