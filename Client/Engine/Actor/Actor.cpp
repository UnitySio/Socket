#include "Actor.h"

#include "../EventManager.h"
#include "../Enums.h"
#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

Actor::Actor(b2World* world, const std::wstring& name) :
    world_(world),
    body_(nullptr),
    is_active_(true),
    is_destroy_(false),
    components_()
{
    name_ = name;
    
    b2BodyDef body_def;
    body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
    body_def.position.Set(0.f, 0.f);

    body_ = world->CreateBody(&body_def);
}

Actor::~Actor()
{
    body_->GetWorld()->DestroyBody(body_);
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

b2World* Actor::GetWorld() const
{
    return body_->GetWorld();
}
