#include "pch.h"
#include "Actor.h"

#include "Enums.h"
#include "Component/RigidBodyComponent.h"
#include "Component/TransformComponent.h"
#include "Level/World.h"
#include "Time/TimerManager.h"

Actor::Actor(const std::wstring& kName) :
    tag_(ActorTag::kNone),
    layer_(ActorLayer::kDefault),
    is_pending_destroy_(false),
    components_(),
    transform_(nullptr),
    parent_(nullptr),
    children_()
{
    name_ = kName;
    
    TransformComponent* transform = CreateComponent<TransformComponent>(L"Transform");
    transform_ = transform->GetSharedThis();
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
    if (b2Body_IsValid(body_id_) && !b2Body_IsEnabled(body_id_)) b2Body_Enable(body_id_);
    
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
    // b2WorldId world_id = World::Get()->world_id_;
    // b2ContactEvents contact_events = b2World_GetContactEvents(world_id);
    // for (MathTypes::uint32 i = 0; i < contact_events.beginCount; ++i)
    // {
    //     b2ContactBeginTouchEvent* contact_event = contact_events.beginEvents + i;
    //     
    //     b2BodyId body_a_id = b2Shape_GetBody(contact_event->shapeIdA);
    //     b2BodyId body_b_id = b2Shape_GetBody(contact_event->shapeIdB);
    //
    //     Actor* actor_a = static_cast<Actor*>(b2Body_GetUserData(body_a_id));
    //     Actor* actor_b = static_cast<Actor*>(b2Body_GetUserData(body_b_id));
    //
    //     if (!actor_a || !actor_b) continue;
    //     
    //     actor_a->OnCollisionEnter(actor_b);
    //     actor_b->OnCollisionEnter(actor_a);
    // }
    //
    // b2SensorEvents sensor_events = b2World_GetSensorEvents(world_id);
    
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

    if (!b2Body_IsValid(body_id_) || !b2Body_IsValid(actor->body_id_)) return;

    const RigidBodyComponent* rigid_body = GetComponent<RigidBodyComponent>();
    const RigidBodyComponent* parent_rigid_body = actor->GetComponent<RigidBodyComponent>();

    if (parent_rigid_body && !rigid_body)
    {
        b2Body_SetType(body_id_, b2Body_GetType(actor->body_id_));
        
        b2WeldJointDef joint_def;
        joint_def.bodyIdA = actor->body_id_;
        joint_def.bodyIdB = body_id_;
        joint_def.localAnchorA = b2Body_GetLocalPoint(actor->body_id_, {0.f, 0.f}); // Center 값 구해서 변경 필요
        joint_def.localAnchorB = b2Body_GetLocalPoint(body_id_, {0.f, 0.f}); // Center 값 구해서 변경 필요
        joint_def.referenceAngle = b2Rot_GetAngle(b2Body_GetRotation(body_id_)) - b2Rot_GetAngle(b2Body_GetRotation(actor->body_id_));

        joint_id_ = b2CreateWeldJoint(World::Get()->world_id_, &joint_def);
    }
}

void Actor::DetachFromActor()
{
    if (!parent_) return;

    std::erase(parent_->children_, this);
    
    if (b2Joint_IsValid(joint_id_))
    {
        b2DestroyJoint(joint_id_);
        joint_id_ = b2_nullJointId;
    }

    parent_ = nullptr;
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
