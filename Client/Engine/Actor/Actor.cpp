#include "Actor.h"

#include "../EventManager.h"
#include "../Enums.h"
#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

Actor::Actor(b2World* world, const std::wstring& kName) :
    root_component_(nullptr),
    world_(world),
    is_active_(true),
    is_destroy_(false),
    components_()
{
    name_ = kName;
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
}

void Actor::Tick(float delta_time)
{
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

void Actor::Destroy()
{
    EventManager::GetInstance()->AddEvent(
        {
            EventType::kDestroyActor,
            reinterpret_cast<uintptr_t>(this)
        });
}

void Actor::Destroy(const Actor* other)
{
    EventManager::GetInstance()->AddEvent(
        {
            EventType::kDestroyActor,
            reinterpret_cast<uintptr_t>(other)
        });
}

void Actor::SpawnActor(const Actor* actor)
{
    EventManager::GetInstance()->AddEvent(
        {
            EventType::kSpawnActor,
            reinterpret_cast<uintptr_t>(actor)
        });
}

void Actor::SetActive(bool active)
{
    EventManager::GetInstance()->AddEvent(
        {
            EventType::kActiveActor,
            reinterpret_cast<uintptr_t>(this),
            static_cast<bool>(active)
        });
}
