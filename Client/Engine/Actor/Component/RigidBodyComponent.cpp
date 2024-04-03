#include "RigidBodyComponent.h"

#include "TransformComponent.h"
#include "Actor/Actor.h"
#include "box2d/b2_body.h"
#include "Vector.h"

RigidBodyComponent::RigidBodyComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName)
{
    if (!GetOwner()->body_) GetOwner()->CreateBody();
}

void RigidBodyComponent::SetBodyType(BodyType type)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->body_;
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

    b2Body* body = owner->body_;
    assert(body);

    body->SetGravityScale(scale);
}

void RigidBodyComponent::SetSleepMode(SleepMode mode)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->body_;
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

    b2Body* body = owner->body_;
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

    b2Body* body = owner->body_;
    assert(body);

    body->SetFixedRotation(freeze);
}

void RigidBodyComponent::SetVelocity(const Vector& kVelocity)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->body_;
    assert(body);

    body->SetLinearVelocity({kVelocity.x, kVelocity.y});
}

void RigidBodyComponent::SetAngularVelocity(float velocity)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->body_;
    assert(body);

    body->SetAngularVelocity(velocity);
}

void RigidBodyComponent::AddForce(const Vector& kForce, ForceMode mode)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->body_;
    assert(body);

    switch (mode)
    {
    case ForceMode::kForce:
        body->ApplyForce({kForce.x, kForce.y}, body->GetWorldCenter(), true);
        break;

    case ForceMode::kImpulse:
        body->ApplyLinearImpulse({kForce.x, kForce.y}, body->GetWorldCenter(), true);
        break;
    }
}

void RigidBodyComponent::AddForceAtPosition(const Vector& kForce, const Vector& kLocation, ForceMode mode)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->body_;
    assert(body);

    switch (mode)
    {
    case ForceMode::kForce:
        body->ApplyForce({kForce.x, kForce.y}, {kLocation.x, kLocation.y}, true);
        break;

    case ForceMode::kImpulse:
        body->ApplyLinearImpulse({kForce.x, kForce.y}, {kLocation.x, kLocation.y}, true);
        break;
    }
}

void RigidBodyComponent::AddTorque(float torque, ForceMode mode)
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->body_;
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

    b2Body* body = owner->body_;
    assert(body);

    body->SetAwake(false);
}

void RigidBodyComponent::WakeUp()
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->body_;
    assert(body);

    body->SetAwake(true);
}

Vector RigidBodyComponent::GetVelocity() const
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->body_;
    assert(body);

    return {body->GetLinearVelocity().x, body->GetLinearVelocity().y};
}

float RigidBodyComponent::GetAngularVelocity() const
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->body_;
    assert(body);

    return body->GetAngularVelocity();
}

bool RigidBodyComponent::IsAwake() const
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->body_;
    assert(body);

    return body->IsAwake();
}

b2BodyType RigidBodyComponent::GetBodyType() const
{
    Actor* owner = GetOwner();
    assert(owner);

    b2Body* body = owner->body_;
    assert(body);

    return body->GetType();
}
