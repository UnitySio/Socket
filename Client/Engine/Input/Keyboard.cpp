#include "pch.h"
#include "Keyboard.h"

#include <ranges>

Keyboard::Keyboard() :
    key_events_(),
    key_states_()
{
}

bool Keyboard::PollEvents(KeyEvnet& event)
{
	std::lock_guard<std::mutex> lock(mutex_);
    if (key_events_.empty()) return false;

    event = key_events_.front();
    key_events_.pop();

    return true;
}

bool Keyboard::GetKeyState(WORD key_code)
{
    return key_states_[key_code];
}

bool Keyboard::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
    if (message == WM_KEYDOWN || message == WM_SYSKEYDOWN ||
        message == WM_KEYUP || message == WM_SYSKEYUP)
    {
        WORD key_code = LOWORD(wParam);
        WORD key_flags = HIWORD(lParam);
        
        MathTypes::uint32 scancode =  MapVirtualKey(key_code, MAPVK_VK_TO_CHAR);

        bool is_released = (key_flags & KF_UP) == KF_UP;
        bool is_repeat = (key_flags & KF_REPEAT) == KF_REPEAT;

        key_states_[key_code] = !is_released;

        KeyAction action = KeyAction::kPressed;
        if (is_released) action = KeyAction::kReleased;

        KeyEvnet new_event = {
            action,
            key_code,
            0,
            is_repeat
        };

        key_events_.push(new_event);
        return true;
    }
    
    if (message == WM_CHAR)
    {
        const WCHAR kCharacter = static_cast<WCHAR>(wParam);
        if (kCharacter < 32 || (kCharacter > 126 && kCharacter < 160)) return false;

        KeyEvnet new_event = {
            KeyAction::kText,
            0,
            kCharacter,
            false
        };

        key_events_.push(new_event);
        return true;
    }
    
    return false;
}

void Keyboard::Clear()
{
    std::lock_guard<std::mutex> lock(mutex_);
    key_events_ = std::queue<KeyEvnet>();

    for (auto& key_state : key_states_ | std::views::values)
    {
        key_state = false;
    }
}
