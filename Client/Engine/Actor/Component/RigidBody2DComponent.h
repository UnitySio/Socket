#pragma once
#include "ActorComponent.h"
#include "box2d/types.h"

namespace Math
{
    struct Vector2;
}

enum class BodyType : MathTypes::uint64
{
    kDynamic = 0,
    kKinematic,
    kStatic
};

enum class SleepMode : MathTypes::uint64
{
    kNeverSleep = 0,
    kStartAwake
};

enum class CollisionDetectionMode : MathTypes::uint64
{
    kDiscrete = 0,
    kContinuous
};

enum class ForceMode : MathTypes::uint64
{
    kForce = 0,
    kImpulse
};

class RigidBody2DComponent : public ActorComponent
{
    SHADER_CLASS_HELPER(RigidBody2DComponent)
    
public:
    RigidBody2DComponent(Actor* owner, const std::wstring& kName);
    virtual ~RigidBody2DComponent() override = default;

    void SetBodyType(BodyType type);
    void SetGravityScale(float scale);
    void SetSleepMode(SleepMode mode);
    void SetCollisionDetectionMode(CollisionDetectionMode mode);
    void SetFreezeRotation(bool freeze);
    void SetLinearVelocity(const Math::Vector2& kLinearVelocity);
    void SetLinearVelocityX(float linear_velocity);
    void SetLinearVelocityY(float linear_velocity);
    void SetAngularVelocity(float velocity);
    void AddForce(const Math::Vector2& kForce, ForceMode mode = ForceMode::kForce);
    void AddForceX(float force, ForceMode mode = ForceMode::kForce);
    void AddForceY(float force, ForceMode mode = ForceMode::kForce);
    void AddForceAtPosition(const Math::Vector2& kForce, const Math::Vector2& kPosition, ForceMode mode = ForceMode::kForce);
    void AddTorque(float torque, ForceMode mode = ForceMode::kForce);
    void UseAutoMass(bool use_auto_mass);
    void SetMass(float mass);
    void Sleep();
    void WakeUp();

    Math::Vector2 GetLinearVelocity() const;
    
    float GetAngularVelocity() const;
    float GetLinearVelocityX() const;
    float GetLinearVelocityY() const;

    bool IsAwake() const;

    BodyType GetBodyType() const;

private:
    b2BodyId GetValidBodyId() const;
    
};
