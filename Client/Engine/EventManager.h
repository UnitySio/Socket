#pragma once
#include <cstdint>
#include <vector>

#include "Singleton.h"

enum class EventType : size_t;

struct Event
{
    EventType type;
    uintptr_t wParam;
    uintptr_t lParam;
};

class EventManager : public Singleton<EventManager>
{
public:
    EventManager();
    virtual ~EventManager() final = default;

    void Tick();
    void AddEvent(const Event& event);

private:
    void ExcuteEvent(const Event& event);
    
    std::vector<Event> events_;
    
};
