#include "pch.h"
#include "Actor.h"

#include <iostream>

#include "EventManager.h"
#include "Enums.h"
#include "box2d/b2_body.h"
#include "box2d/b2_weld_joint.h"
#include "box2d/b2_world.h"
#include "Component/RigidBodyComponent.h"
#include "Component/TransformComponent.h"
#include "Level/World.h"
#include "Time/TimerManager.h"

Actor::Actor(const std::wstring& kName) :
    tag_(ActorTag::kNone),
    layer_(ActorLayer::kDefault),
    body_(nullptr),
    is_active_(true),
    is_destroy_(false),
    components_(),
    transform_(nullptr),
    parent_(nullptr),
    children_(),
    parent_joint_(nullptr)
{
    name_ = kName;
    
    TransformComponent* transform = CreateComponent<TransformComponent>(L"Transform");
    transform_ = std::static_pointer_cast<TransformComponent>(transform->GetSharedPtr());
}

void Actor::OnCollisionEnter(Actor* other)
{
    on_collision_enter.Execute(std::move(other));
    if (parent_) parent_->OnCollisionEnter(other);
}

void Actor::OnCollisionStay(Actor* other)
{
    on_collision_stay.Execute(std::move(other));
    if (parent_) parent_->OnCollisionStay(other);
}

void Actor::OnCollisionExit(Actor* other)
{
    on_collision_exit.Execute(std::move(other));
    if (parent_) parent_->OnCollisionExit(other);
}

void Actor::OnTriggerEnter(Actor* other)
{
    on_trigger_enter.Execute(std::move(other));
    if (parent_) parent_->OnTriggerEnter(other);
}

void Actor::OnTriggerStay(Actor* other)
{
    on_trigger_stay.Execute(std::move(other));
    if (parent_) parent_->OnTriggerStay(other);
}

void Actor::OnTriggerExit(Actor* other)
{
    on_trigger_exit.Execute(std::move(other));
    if (parent_) parent_->OnTriggerExit(other);
}

void Actor::BeginPlay()
{
    if (body_ && !body_->IsEnabled()) body_->SetEnabled(true);
    
    for (const auto& component : components_)
    {
        component->BeginPlay();
    }
}

void Actor::EndPlay(EndPlayReason type)
{
    for (const auto& component : components_)
    {
        component->EndPlay(type);
    }
    
    UninitializeComponents();

    components_.clear();

    if (parent_joint_)
    {
        World::Get()->physics_world_->DestroyJoint(parent_joint_);
        parent_joint_ = nullptr;
    }

    if (body_)
    {
        World::Get()->physics_world_->DestroyBody(body_);
        body_ = nullptr;
    }
}

void Actor::PhysicsTick(float delta_time)
{
    for (const auto& component : components_)
    {
        component->PhysicsTickComponent(delta_time);
    }
}

void Actor::Tick(float delta_time)
{
    for (const auto& component : components_)
    {
        component->TickComponent(delta_time);
    }
}

void Actor::PostTick(float delta_time)
{
    for (const auto& component : components_)
    {
        component->PostTickComponent(delta_time);
    }
}

void Actor::Render(float alpha)
{
    for (const auto& component : components_)
    {
        component->Render(alpha);
    }
}

void Actor::AttachToActor(Actor* actor)
{
    parent_ = actor;
    actor->children_.push_back(this);

    transform_->SetRelativePosition(transform_->GetWorldPosition() - actor->transform_->GetWorldPosition());

    if (!body_ || !actor->body_) return;

    const RigidBodyComponent* rigid_body = GetComponent<RigidBodyComponent>();
    const RigidBodyComponent* parent_rigid_body = actor->GetComponent<RigidBodyComponent>();

    if (parent_rigid_body && !rigid_body)
    {
        body_->SetType(actor->body_->GetType());
        
        b2WeldJointDef joint_def;
        joint_def.bodyA = actor->body_;
        joint_def.bodyB = body_;
        joint_def.localAnchorA = actor->body_->GetLocalCenter();
        joint_def.localAnchorB = body_->GetLocalPoint(actor->body_->GetWorldCenter());
        joint_def.referenceAngle = body_->GetAngle() - actor->body_->GetAngle();

        parent_joint_ = World::Get()->physics_world_->CreateJoint(&joint_def);
    }
}

void Actor::DetachFromActor()
{
    if (!parent_) return;

    std::erase(parent_->children_, this);
    if (parent_joint_) World::Get()->physics_world_->DestroyJoint(parent_joint_);

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

void Actor::SetActive(bool active)
{
    EventManager::Get()->AddEvent(
        {
            EventType::kActiveActor,
            reinterpret_cast<uintptr_t>(this),
            static_cast<bool>(active)
        });
}

void Actor::SetLifeSpan(float life_span)
{
    if (life_span > 0.f)
    {
        life_span_timer_ = TimerManager::Get()->SetTimer(this, &Actor::OnLifeSpanExpired, life_span);
    }
    else
    {
        TimerManager::Get()->ClearTimer(life_span_timer_);
    }
}

bool Actor::CompareTag(ActorTag tag) const
{
    return tag_ == tag;
}

void Actor::InitializeActor()
{
    PreInitializeComponents();
    InitializeComponents();
    PostInitializeComponents();
}

void Actor::InitializeComponents()
{
    for (const auto& component : components_)
    {
        component->InitializeComponent();
    }
}

void Actor::UninitializeComponents()
{
    for (const auto& component : components_)
    {
        component->UninitializeComponent();
    }
}

void Actor::Destroyed()
{
    EndPlay(EndPlayReason::kDestroyed);
}

void Actor::CreateBody()
{
    b2BodyDef body_def;
    body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

    body_ = World::Get()->physics_world_->CreateBody(&body_def);
    body_->SetEnabled(false);
}

void Actor::OnLifeSpanExpired()
{
    Destroy();
}
