#include "pch.h"
#include "RigidBodyComponent.h"

#include "TransformComponent.h"
#include "Actor/Actor.h"
#include "Math/Vector2.h"

RigidBodyComponent::RigidBodyComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName)
{
    if (!b2Body_IsValid(GetOwner()->body_id_)) GetOwner()->CreateBody();
}

void RigidBodyComponent::SetBodyType(BodyType type)
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

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

void RigidBodyComponent::SetGravityScale(float scale)
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

    b2Body_SetGravityScale(body_id, scale);
}

void RigidBodyComponent::SetSleepMode(SleepMode mode)
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

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

void RigidBodyComponent::SetCollisionDetectionMode(CollisionDetectionMode mode)
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

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

void RigidBodyComponent::SetFreezeRotation(bool freeze)
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));
    
    b2Body_SetFixedRotation(body_id, freeze);
}

void RigidBodyComponent::SetVelocity(const Math::Vector2& kVelocity)
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));
    
    b2Body_SetLinearVelocity(body_id, {kVelocity.x, kVelocity.y});
}

void RigidBodyComponent::SetAngularVelocity(float velocity)
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

    b2Body_SetAngularVelocity(body_id, velocity);
}

void RigidBodyComponent::AddForce(const Math::Vector2& kForce, ForceMode mode)
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

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

void RigidBodyComponent::AddForceAtPosition(const Math::Vector2& kForce, const Math::Vector2& kPosition, ForceMode mode)
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

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

void RigidBodyComponent::AddTorque(float torque, ForceMode mode)
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

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

void RigidBodyComponent::Sleep()
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

    b2Body_SetAwake(body_id, false);
}

void RigidBodyComponent::WakeUp()
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

    b2Body_SetAwake(body_id, true);
}

Math::Vector2 RigidBodyComponent::GetVelocity() const
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

    b2Vec2 velocity = b2Body_GetLinearVelocity(body_id);
    return {velocity.x, velocity.y};
}

float RigidBodyComponent::GetAngularVelocity() const
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

    return b2Body_GetAngularVelocity(body_id);
}

bool RigidBodyComponent::IsAwake() const
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

    return b2Body_IsAwake(body_id);
}

b2BodyType RigidBodyComponent::GetBodyType() const
{
    Actor* owner = GetOwner();
    CHECK(owner);

    b2BodyId body_id = owner->body_id_;
    CHECK(b2Body_IsValid(body_id));

    return b2Body_GetType(body_id);
}
