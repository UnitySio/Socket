#pragma once
#include "ActorComponent.h"
#include "box2d/types.h"

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

class RigidBody2DComponent : public ActorComponent
{
    SHADER_CLASS_HELPER(RigidBody2DComponent)
    
public:
    RigidBody2DComponent(class Actor* owner, const std::wstring& kName);
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
    void Sleep();
    void WakeUp();

    Math::Vector2 GetVelocity() const;
    
    float GetAngularVelocity() const;
    float GetLinearVelocityX() const;
    float GetLinearVelocityY() const;

    bool IsAwake() const;

    b2BodyType GetBodyType() const;
    
};
