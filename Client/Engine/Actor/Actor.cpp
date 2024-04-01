#include "Actor.h"

#include "EventManager.h"
#include "Enums.h"
#include "Component/TransformComponent.h"

Actor::Actor(b2World* world, const std::wstring& kName) :
    world_(world),
    previous_location_(Vector::Zero()),
    previous_angle_(0.f),
    is_active_(true),
    is_destroy_(false),
    components_(),
    transform_(nullptr)
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
