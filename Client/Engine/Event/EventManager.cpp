#include "pch.h"
#include "EventManager.h"

EventManager::EventManager() :
    events_()
{
}

bool EventManager::PollEvent(Event& event)
{
    if (events_.empty()) return false;

    event = events_.front();
    events_.pop();

    return true;
}

bool EventManager::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
    if (message == WM_KEYDOWN || message == WM_SYSKEYDOWN ||
        message == WM_KEYUP || message == WM_SYSKEYUP)
    {
        WORD key_code = LOWORD(wParam);
        WORD key_flags = HIWORD(lParam);
        
        MathTypes::uint32 scancode =  MapVirtualKey(key_code, MAPVK_VK_TO_CHAR);

        bool is_released = (key_flags & KF_UP) == KF_UP;
        bool is_repeat = (key_flags & KF_REPEAT) == KF_REPEAT;

        MathTypes::uint32 type = 0;
        if (!is_released) type = EventType::kKeyPressed;
        else type = EventType::kKeyReleased;

        Event event;
        event.type = type;
        event.key.key_code = key_code;
        event.key.is_repeat = is_repeat;

        events_.push(event);
        return true;
    }
    
    if (message == WM_CHAR)
    {
        const WCHAR kCharacter = static_cast<WCHAR>(wParam);
        if (kCharacter < 32 || (kCharacter > 126 && kCharacter < 160)) return false;

        Event event;
        event.type = EventType::kText;
        event.text.character = kCharacter;

        events_.push(event);
        return true;
    }
    
    return false;
}
