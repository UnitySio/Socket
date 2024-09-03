﻿#include "pch.h"
#include "Actor.h"

#include "Enums.h"
#include "box2d/box2d.h"
#include "Component/TransformComponent.h"
#include "Level/World.h"

Actor::Actor(const std::wstring& kName) :
    tag_(ActorTag::kNone),
    layer_(ActorLayer::kDefault),
    is_pending_destroy_(false),
    components_(),
    transform_(nullptr)
{
    name_ = kName;
    
    TransformComponent* transform = AddComponent<TransformComponent>(L"Transform");
    transform_ = transform->GetSharedThis();
}

void Actor::OnCollisionEnter(Actor* other)
{
    on_collision_enter.Execute(std::move(other));
}

void Actor::OnCollisionExit(Actor* other)
{
    on_collision_exit.Execute(std::move(other));
}

void Actor::OnTriggerEnter(Actor* other)
{
    on_trigger_enter.Execute(std::move(other));
}

void Actor::OnTriggerExit(Actor* other)
{
    on_trigger_exit.Execute(std::move(other));
}

void Actor::BeginPlay()
{
    if (b2Body_IsValid(body_id_) && !b2Body_IsEnabled(body_id_)) b2Body_Enable(body_id_);
    
    for (const auto& kComponent : components_)
    {
        kComponent->BeginPlay();
    }
}

void Actor::EndPlay(EndPlayReason type)
{
    for (const auto& kComponent : components_)
    {
        kComponent->EndPlay(type);
    }
    
    UninitializeComponents();

    components_.clear();

    if (b2Joint_IsValid(joint_id_))
    {
        b2DestroyJoint(joint_id_);
        joint_id_ = b2_nullJointId;
    }

    if (b2Body_IsValid(body_id_))
    {
        b2DestroyBody(body_id_);
        body_id_ = b2_nullBodyId;
    }
}

void Actor::Destroyed()
{
    EndPlay(EndPlayReason::kDestroyed);
}

void Actor::PhysicsTick(float delta_time)
{
    for (const auto& kComponent : components_)
    {
        kComponent->PhysicsTickComponent(delta_time);
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

void Actor::Destroy()
{
    World::Get()->DestroyActor(this);
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

void Actor::CreateBody()
{
    b2BodyDef body_def = b2DefaultBodyDef();
    body_def.userData = this;

    body_id_ = b2CreateBody(World::Get()->world_id_, &body_def);
    b2Body_Disable(body_id_);
}

void Actor::OnLifeSpanExpired()
{
    Destroy();
}
