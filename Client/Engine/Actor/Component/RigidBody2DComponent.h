﻿#pragma once
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
    GENERATED_BODY(RigidBody2DComponent, ActorComponent)
    
public:
    RigidBody2DComponent(Actor* owner, const std::wstring& kName);
    virtual ~RigidBody2DComponent() override = default;

    virtual void InitializeComponent() override;

    void SetBodyType(BodyType type);
    void SetGravityScale(float scale);
    void SetSleepMode(SleepMode mode);
    void SetCollisionDetectionMode(CollisionDetectionMode mode);
    void SetFreezeRotation(bool freeze);
    void UseAutoMass(bool use_auto_mass);
    void SetMass(float mass);
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

    Math::Vector2 GetLinearVelocity() const;
    
    float GetAngularVelocity() const;
    float GetLinearVelocityX() const;
    float GetLinearVelocityY() const;

    bool IsAwake() const;

    BodyType GetBodyType() const;

private:
    void SetBodyTypeInternal(b2BodyId body_id);
    void SetGravityScaleInternal(b2BodyId body_id);
    void SetSleepModeInternal(b2BodyId body_id);
    void SetCollisionDetectionModeInternal(b2BodyId body_id);
    void SetFixedRotationInternal(b2BodyId body_id);
    void SetAutoMassInternal(b2BodyId body_id);
    void SetMassInternal(b2BodyId body_id);
    
    b2BodyId GetValidBodyId() const;

    BodyType body_type_;
    SleepMode sleep_mode_;
    CollisionDetectionMode collision_detection_mode_;

    float gravity_scale_;
    float mass_;

    bool is_fixed_rotation_;
    bool use_auto_mass_;
    
};
