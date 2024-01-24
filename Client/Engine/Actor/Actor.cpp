#include "Actor.h"

#include "../EventManager.h"
#include "../Enums.h"
#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

Actor::Actor(b2World* world) : is_active_(true), is_destroy_(false)
{
    b2BodyDef body_def;
    body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
    body_def.position.Set(0.0f, 0.0f);

    body_ = world->CreateBody(&body_def);
}

Actor::~Actor()
{
    body_->GetWorld()->DestroyBody(body_);
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
