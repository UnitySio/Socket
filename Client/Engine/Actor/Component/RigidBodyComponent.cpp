#include "RigidBodyComponent.h"

#include "../Actor.h"
#include "box2d/b2_body.h"
#include "../../Vector.h"

RigidBodyComponent::RigidBodyComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName)
{
}

void RigidBodyComponent::SetBodyType(BodyType type)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    switch (type)
    {
    case BodyType::kDynamic:
        body->SetType(b2_dynamicBody);
        break;

    case BodyType::kKinematic:
        body->SetType(b2_kinematicBody);
        break;

    case BodyType::kStatic:
        body->SetType(b2_staticBody);
        break;
    }
}

void RigidBodyComponent::SetGravityScale(float scale)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    body->SetGravityScale(scale);
}

void RigidBodyComponent::SetSleepMode(SleepMode mode)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    switch (mode)
    {
    case SleepMode::kNeverSleep:
        body->SetSleepingAllowed(false);
        break;

    case SleepMode::kStartAwake:
        body->SetSleepingAllowed(true);
        break;
    }
}

void RigidBodyComponent::SetCollisionDetectionMode(CollisionDetectionMode mode)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    switch (mode)
    {
    case CollisionDetectionMode::kDiscrete:
        body->SetBullet(false);
        break;

    case CollisionDetectionMode::kContinuous:
        body->SetBullet(true);
        break;
    }
}

void RigidBodyComponent::SetFreezeRotation(bool freeze)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    body->SetFixedRotation(freeze);
}

void RigidBodyComponent::SetVelocity(const Vector& velocity)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    body->SetLinearVelocity({velocity.x, velocity.y});
}

void RigidBodyComponent::SetAngularVelocity(float velocity)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    body->SetAngularVelocity(velocity);
}

void RigidBodyComponent::AddForce(const Vector& force, ForceMode mode)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    switch (mode)
    {
    case ForceMode::kForce:
        body->ApplyForce({force.x, force.y}, body->GetWorldCenter(), true);
        break;

    case ForceMode::kImpulse:
        body->ApplyLinearImpulse({force.x, force.y}, body->GetWorldCenter(), true);
        break;
    }
}

void RigidBodyComponent::AddForceAtPosition(const Vector& force, const Vector& position, ForceMode mode)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    switch (mode)
    {
    case ForceMode::kForce:
        body->ApplyForce({force.x, force.y}, {position.x, position.y}, true);
        break;

    case ForceMode::kImpulse:
        body->ApplyLinearImpulse({force.x, force.y}, {position.x, position.y}, true);
        break;
    }
}

void RigidBodyComponent::AddTorque(float torque, ForceMode mode)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    switch (mode)
    {
    case ForceMode::kForce:
        body->ApplyTorque(torque, true);
        break;

    case ForceMode::kImpulse:
        body->ApplyAngularImpulse(torque, true);
        break;
    }
}

void RigidBodyComponent::Sleep()
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    body->SetAwake(false);
}

void RigidBodyComponent::WakeUp()
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    body->SetAwake(true);
}

Vector RigidBodyComponent::GetVelocity() const
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    return {body->GetLinearVelocity().x, body->GetLinearVelocity().y};
}

float RigidBodyComponent::GetAngularVelocity() const
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->GetBody();
    assert(body);

    return body->GetAngularVelocity();
}
