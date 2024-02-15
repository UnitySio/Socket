#include "EventManager.h"

#include "Enums.h"
#include "Actor/Actor.h"
#include "Level/Level.h"
#include "Level/LevelManager.h"

EventManager::EventManager() : events_()
{
}

void EventManager::Tick()
{
    for (auto& event : events_)
    {
        ExcuteEvent(event);
    }

    events_.clear();
}

void EventManager::AddEvent(const Event& event)
{
    events_.push_back(event);
}

void EventManager::ExcuteEvent(const Event& event)
{
    switch (event.type)
    {
    case EventType::kSpawnActor:
        {
            Actor* actor = reinterpret_cast<Actor*>(event.wParam);
            Level* level = LevelManager::Get()->GetLevel();
            level->AddActor(actor);
            actor->BeginPlay();
        }
        break;
        
    case EventType::kDestroyActor:
        {
            Actor* actor = reinterpret_cast<Actor*>(event.wParam);
            actor->OnDestroyed();
            actor->is_destroy_ = true;
        }
        break;

    case EventType::kActiveActor:
        {
            Actor* actor = reinterpret_cast<Actor*>(event.wParam);
            bool active = static_cast<bool>(event.lParam);
            actor->is_active_ = active;
        }
        break;
    }
}
