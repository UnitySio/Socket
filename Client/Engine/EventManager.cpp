#include "EventManager.h"

#include "Enums.h"
#include "GameEngine.h"
#include "Actor/Actor.h"
#include "Level/Level.h"
#include "Level/World.h"

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

void EventManager::AddEvent(const Event& kEvent)
{
    events_.push_back(kEvent);
}

void EventManager::ExcuteEvent(const Event& kEvent)
{
    switch (kEvent.type)
    {
    case EventType::kSpawnActor:
        {
            Actor* actor = reinterpret_cast<Actor*>(kEvent.wParam);
            Level* level = World::Get()->GetLevel();
            level->AddActor(std::shared_ptr<Actor>(actor));
            actor->InitializeActor();
        }
        break;

    case EventType::kDestroyActor:
        {
            Actor* actor = reinterpret_cast<Actor*>(kEvent.wParam);
            actor->is_destroy_ = true;
        }
        break;

    case EventType::kActiveActor:
        {
            Actor* actor = reinterpret_cast<Actor*>(kEvent.wParam);
            bool active = static_cast<bool>(kEvent.lParam);
            actor->is_active_ = active;
        }
        break;

    case EventType::kLevelTransition:
        {
            LevelType level_type = static_cast<LevelType>(kEvent.wParam);
            World::Get()->OpenLevel(level_type);
        }
    }
}
