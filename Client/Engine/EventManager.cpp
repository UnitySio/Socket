#include "EventManager.h"

#include "Enums.h"
#include "Actor/Actor.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

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
            Scene* scene = SceneManager::GetInstance()->GetCurrentScene();
            scene->AddActor(actor);
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
