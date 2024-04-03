#include "Actor.h"

#include <iostream>

#include "EventManager.h"
#include "Enums.h"
#include "box2d/b2_body.h"
#include "box2d/b2_weld_joint.h"
#include "box2d/b2_world.h"
#include "Component/RigidBodyComponent.h"
#include "Component/TransformComponent.h"

Actor::Actor(b2World* world, const std::wstring& kName) :
    world_(world),
    body_(nullptr),
    previous_location_(Vector::Zero()),
    previous_angle_(0.f),
    is_active_(true),
    is_destroy_(false),
    components_(),
    transform_(nullptr),
    parent_(nullptr),
    children_(),
    parent_joint_(nullptr)
{
    name_ = kName;

    transform_ = CreateComponent<TransformComponent>(L"Transform");
}

void Actor::BeginPlay()
{
    for (const auto& component : components_)
    {
        component->BeginPlay();
    }
}

void Actor::EndPlay()
{
    for (const auto& component : components_)
    {
        component->EndPlay();
    }

    if (!parent_joint_) world_->DestroyJoint(parent_joint_);
    if (!body_) world_->DestroyBody(body_);
}

void Actor::PhysicsTick(float delta_time)
{
}

void Actor::Tick(float delta_time)
{
    for (const auto& component : components_)
    {
        component->TickComponent(delta_time);
    }
}

void Actor::Render()
{
    for (const auto& component : components_)
    {
        component->Render();
    }
}

void Actor::AttachToActor(Actor* actor)
{
    parent_ = actor;
    actor->children_.push_back(this);

    transform_->SetRelativeLocation(transform_->GetWorldLocation() - actor->transform_->GetWorldLocation());

    if (!body_ || !actor->body_) return;

    body_->SetType(actor->body_->GetType());

    const RigidBodyComponent* rigid_body = GetComponent<RigidBodyComponent>();
    const RigidBodyComponent* parent_rigid_body = actor->GetComponent<RigidBodyComponent>();

    if (parent_rigid_body && !rigid_body)
    {
        b2WeldJointDef joint_def;
        joint_def.bodyA = actor->body_;
        joint_def.bodyB = body_;
        joint_def.localAnchorA = actor->body_->GetLocalCenter();
        joint_def.localAnchorB = body_->GetLocalPoint(actor->body_->GetWorldCenter());
        joint_def.referenceAngle = body_->GetAngle() - actor->body_->GetAngle();

        parent_joint_ = world_->CreateJoint(&joint_def);
    }
}

void Actor::DetachFromActor()
{
    if (!parent_) return;

    std::erase(parent_->children_, this);

    if (!parent_joint_) world_->DestroyJoint(parent_joint_);

    parent_ = nullptr;
    parent_joint_ = nullptr;
}

void Actor::Destroy()
{
    EventManager::Get()->AddEvent(
        {
            EventType::kDestroyActor,
            reinterpret_cast<uintptr_t>(this)
        });
}

void Actor::Destroy(const Actor* kOther)
{
    EventManager::Get()->AddEvent(
        {
            EventType::kDestroyActor,
            reinterpret_cast<uintptr_t>(kOther)
        });
}

void Actor::SpawnActor(const Actor* kActor)
{
    EventManager::Get()->AddEvent(
        {
            EventType::kSpawnActor,
            reinterpret_cast<uintptr_t>(kActor)
        });
}

void Actor::SetActive(bool active)
{
    EventManager::Get()->AddEvent(
        {
            EventType::kActiveActor,
            reinterpret_cast<uintptr_t>(this),
            static_cast<bool>(active)
        });
}

void Actor::CreateBody()
{
    b2BodyDef body_def;
    body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

    body_ = world_->CreateBody(&body_def);
}
