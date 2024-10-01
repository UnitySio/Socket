#pragma once
#include <queue>
#include <Windows.h>

#include "Events.h"
#include "Singleton.h"

class EventManager : public Singleton<EventManager>
{
public:
    EventManager();
    virtual ~EventManager() override = default;

    bool PollEvent(Event& event);
    bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);

private:
    std::queue<Event> events_;
    
};
