#include "pch.h"
#include "RigidBody2DComponent.h"

#include "TransformComponent.h"
#include "Actor/Actor.h"
#include "box2d/box2d.h"
#include "Math/Vector2.h"

RigidBody2DComponent::RigidBody2DComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName)
{
    if (!b2Body_IsValid(GetOwner()->body_id_)) GetOwner()->CreateBody();
}

void RigidBody2DComponent::SetBodyType(BodyType type)
{
    b2BodyId body_id = GetValidBodyId();

    switch (type)
    {
    case BodyType::kDynamic:
        b2Body_SetType(body_id, b2_dynamicBody);
        break;

    case BodyType::kKinematic:
        b2Body_SetType(body_id, b2_kinematicBody);
        break;

    case BodyType::kStatic:
        b2Body_SetType(body_id, b2_staticBody);
        break;
    }
}

void RigidBody2DComponent::SetGravityScale(float scale)
{
    b2BodyId body_id = GetValidBodyId();

    b2Body_SetGravityScale(body_id, scale);
}

void RigidBody2DComponent::SetSleepMode(SleepMode mode)
{
    b2BodyId body_id = GetValidBodyId();

    switch (mode)
    {
    case SleepMode::kNeverSleep:
        b2Body_EnableSleep(body_id, false);
        break;

    case SleepMode::kStartAwake:
        b2Body_EnableSleep(body_id, true);
        break;
    }
}

void RigidBody2DComponent::SetCollisionDetectionMode(CollisionDetectionMode mode)
{
    b2BodyId body_id = GetValidBodyId();

    switch (mode)
    {
    case CollisionDetectionMode::kDiscrete:
        b2Body_SetBullet(body_id, false);
        break;

    case CollisionDetectionMode::kContinuous:
        b2Body_SetBullet(body_id, true);
        break;
    }
}

void RigidBody2DComponent::SetFreezeRotation(bool freeze)
{
    b2BodyId body_id = GetValidBodyId();
    
    b2Body_SetFixedRotation(body_id, freeze);
}

void RigidBody2DComponent::SetLinearVelocity(const Math::Vector2& kLinearVelocity)
{
    b2BodyId body_id = GetValidBodyId();
    
    b2Body_SetLinearVelocity(body_id, {kLinearVelocity.x, kLinearVelocity.y});
}

void RigidBody2DComponent::SetLinearVelocityX(float linear_velocity)
{
    b2BodyId body_id = GetValidBodyId();
    
    b2Body_SetLinearVelocity(body_id, {linear_velocity, b2Body_GetLinearVelocity(body_id).y});
}

void RigidBody2DComponent::SetLinearVelocityY(float linear_velocity)
{
    b2BodyId body_id = GetValidBodyId();
    
    b2Body_SetLinearVelocity(body_id, {b2Body_GetLinearVelocity(body_id).x, linear_velocity});
}

void RigidBody2DComponent::SetAngularVelocity(float velocity)
{
    b2BodyId body_id = GetValidBodyId();

    b2Body_SetAngularVelocity(body_id, velocity);
}

void RigidBody2DComponent::AddForce(const Math::Vector2& kForce, ForceMode mode)
{
    b2BodyId body_id = GetValidBodyId();

    switch (mode)
    {
    case ForceMode::kForce:
        b2Body_ApplyForceToCenter(body_id, {kForce.x, kForce.y}, true);
        break;

    case ForceMode::kImpulse:
        b2Body_ApplyLinearImpulseToCenter(body_id, {kForce.x, kForce.y}, true);
        break;
    }
}

void RigidBody2DComponent::AddForceX(float force, ForceMode mode)
{
    b2BodyId body_id = GetValidBodyId();

    switch (mode)
    {
    case ForceMode::kForce:
        b2Body_ApplyForceToCenter(body_id, {force, 0.f}, true);
        break;

    case ForceMode::kImpulse:
        b2Body_ApplyLinearImpulseToCenter(body_id, {force, 0.f}, true);
        break;
    }
}

void RigidBody2DComponent::AddForceY(float force, ForceMode mode)
{
    b2BodyId body_id = GetValidBodyId();

    switch (mode)
    {
    case ForceMode::kForce:
        b2Body_ApplyForceToCenter(body_id, {0.f, force}, true);
        break;

    case ForceMode::kImpulse:
        b2Body_ApplyLinearImpulseToCenter(body_id, {0.f, force}, true);
        break;
    }
}

void RigidBody2DComponent::AddForceAtPosition(const Math::Vector2& kForce, const Math::Vector2& kPosition, ForceMode mode)
{
    b2BodyId body_id = GetValidBodyId();

    switch (mode)
    {
    case ForceMode::kForce:
        b2Body_ApplyForce(body_id, {kForce.x, kForce.y}, {kPosition.x, kPosition.y}, true);
        break;

    case ForceMode::kImpulse:
        b2Body_ApplyLinearImpulse(body_id, {kForce.x, kForce.y}, {kPosition.x, kPosition.y}, true);
        break;
    }
}

void RigidBody2DComponent::AddTorque(float torque, ForceMode mode)
{
    b2BodyId body_id = GetValidBodyId();

    switch (mode)
    {
    case ForceMode::kForce:
        b2Body_ApplyTorque(body_id, torque, true);
        break;

    case ForceMode::kImpulse:
        b2Body_ApplyAngularImpulse(body_id, torque, true);
        break;
    }
}

void RigidBody2DComponent::UseAutoMass(bool use_auto_mass)
{
    b2BodyId body_id = GetValidBodyId();

    if (!use_auto_mass)
    {
        SetMass(1.f);
        return;
    }

    b2Body_ApplyMassFromShapes(body_id);
}

void RigidBody2DComponent::SetMass(float mass)
{
    b2BodyId body_id = GetValidBodyId();

    b2MassData mass_data = b2Body_GetMassData(body_id);
    mass_data.mass = mass;

    b2Body_SetMassData(body_id, mass_data);
    
}

void RigidBody2DComponent::Sleep()
{
    b2BodyId body_id = GetValidBodyId();

    b2Body_SetAwake(body_id, false);
}

void RigidBody2DComponent::WakeUp()
{
    b2BodyId body_id = GetValidBodyId();

    b2Body_SetAwake(body_id, true);
}

Math::Vector2 RigidBody2DComponent::GetVelocity() const
{
    b2BodyId body_id = GetValidBodyId();

    b2Vec2 velocity = b2Body_GetLinearVelocity(body_id);
    return {velocity.x, velocity.y};
}

float RigidBody2DComponent::GetAngularVelocity() const
{
    b2BodyId body_id = GetValidBodyId();

    return b2Body_GetAngularVelocity(body_id);
}

float RigidBody2DComponent::GetLinearVelocityX() const
{
    b2BodyId body_id = GetValidBodyId();

    return b2Body_GetLinearVelocity(body_id).x;
}

float RigidBody2DComponent::GetLinearVelocityY() const
{
    b2BodyId body_id = GetValidBodyId();

    return b2Body_GetLinearVelocity(body_id).y;
}

bool RigidBody2DComponent::IsAwake() const
{
    b2BodyId body_id = GetValidBodyId();

    return b2Body_IsAwake(body_id);
}

BodyType RigidBody2DComponent::GetBodyType() const
{
    b2BodyId body_id = GetValidBodyId();

    if (b2Body_GetType(body_id) == b2_kinematicBody) return BodyType::kKinematic;
    if (b2Body_GetType(body_id) == b2_staticBody) return BodyType::kStatic;
    return BodyType::kDynamic;
}

b2BodyId RigidBody2DComponent::GetValidBodyId() const
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

    return body_id;
}
