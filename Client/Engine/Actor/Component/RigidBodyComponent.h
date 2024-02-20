#pragma once
#include "ActorComponent.h"

struct Vector;

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
public:
    RigidBodyComponent(class Actor* owner, const std::wstring& kName);
    virtual ~RigidBodyComponent() override = default;

    void SetBodyType(BodyType type);
    void SetGravityScale(float scale);
    void SetSleepMode(SleepMode mode);
    void SetCollisionDetectionMode(CollisionDetectionMode mode);
    void SetFreezeRotation(bool freeze);
    void SetVelocity(const Vector& velocity);
    void SetAngularVelocity(float velocity);
    void AddForce(const Vector& force, ForceMode mode = ForceMode::kForce);
    void AddForceAtPosition(const Vector& force, const Vector& position, ForceMode mode = ForceMode::kForce);
    void AddTorque(float torque, ForceMode mode = ForceMode::kForce);
    void Sleep();
    void WakeUp();

    Vector GetVelocity() const;
    
    float GetAngularVelocity() const;

    bool IsAwake() const;
    
};
