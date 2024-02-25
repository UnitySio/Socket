#include "Actor.h"

#include "../EventManager.h"
#include "../Enums.h"
#include "box2d/b2_body.h"
#include "box2d/b2_world.h"
#include "Component/SceneComponent/SceneComponent.h"
#include "../Vector.h"

Actor::Actor(b2World* world, const std::wstring& kName) :
    root_component_(nullptr),
    world_(world),
    body_(nullptr),
    is_active_(true),
    is_destroy_(false),
    components_()
{
    name_ = kName;

    b2BodyDef body_def;
    body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
    
    body_ = world_->CreateBody(&body_def);
}

void Actor::BeginPlay()
{
    for (auto& component : components_)
    {
        component->BeginPlay();
    }
}

void Actor::EndPlay()
{
    for (auto& component : components_)
    {
        component->EndPlay();
    }

    if (body_) world_->DestroyBody(body_);
}

void Actor::PhysicsTick(float delta_time)
{
}

void Actor::Tick(float delta_time)
{
    if (body_)
    {
        if (body_->GetType() == b2_dynamicBody && root_component_)
        {
            root_component_->SetRelativeTransform(body_->GetTransform());
        }
    }
    
    for (auto& component : components_)
    {
        component->TickComponent(delta_time);
    }
}

void Actor::Render()
{
    for (auto& component : components_)
    {
        component->Render();
    }
}

void Actor::AttachToActor(Actor* actor)
{
}

void Actor::Destroy()
{
    EventManager::Get()->AddEvent(
        {
            EventType::kDestroyActor,
            reinterpret_cast<uintptr_t>(this)
        });
}

void Actor::Destroy(const Actor* other)
{
    EventManager::Get()->AddEvent(
        {
            EventType::kDestroyActor,
            reinterpret_cast<uintptr_t>(other)
        });
}

void Actor::SpawnActor(const Actor* actor)
{
    EventManager::Get()->AddEvent(
        {
            EventType::kSpawnActor,
            reinterpret_cast<uintptr_t>(actor)
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

void Actor::SetActorLocation(const b2Vec2& location)
{
    if (!root_component_) return;

    root_component_->SetRelativeLocation(location);
    body_->SetTransform(location, body_->GetAngle());
}

void Actor::SetActorRotation(float rotation)
{
    if (!root_component_) return;

    root_component_->SetRelativeRotation(rotation);
    body_->SetTransform(body_->GetPosition(), rotation);
}

bool Actor::SetRootComponent(SceneComponent* component)
{
    if (component == nullptr || component->GetOwner() == this)
    {
        if (root_component_ != component)
        {
            root_component_ = component;
        }
        
        return true;
    }

    return false;
}

Vector Actor::GetActorLocation() const
{
    if (!root_component_) return Vector::Zero();
    return root_component_->GetRelativeLocation();
}

Vector Actor::GetActorRightVector() const
{
    assert(body_);

    b2Vec2 x = body_->GetTransform().q.GetXAxis();
    return {x.x, x.y};
}

Vector Actor::GetActorUpVector() const
{
    assert(body_);

    b2Vec2 y = body_->GetTransform().q.GetYAxis();
    return {-y.x, -y.y};
}
