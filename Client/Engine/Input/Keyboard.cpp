#include "Keyboard.h"

#include <ranges>

Keyboard::Keyboard() : key_states_()
{
}

void Keyboard::ProcessMessage()
{
    while (!events_.empty())
    {
        events_.front()();
        events_.pop();
    }
}

bool Keyboard::PendingMessage(UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
    if (message == WM_KEYDOWN || message == WM_SYSKEYDOWN ||
        message == WM_KEYUP || message == WM_SYSKEYUP)
    {
        WORD key_code = LOWORD(wParam);
        WORD key_flags = HIWORD(lParam);
        
        MathTypes::uint32 char_code =  MapVirtualKey(key_code, MAPVK_VK_TO_CHAR);

        bool is_released = (key_flags & KF_UP) == KF_UP;
        bool is_repeat = (key_flags & KF_REPEAT) == KF_REPEAT;
        
        if (!is_released)
        {
            Function<bool(WORD, MathTypes::uint32, bool)> f(this, &Keyboard::OnKeyDown, key_code, char_code, is_repeat);
            events_.push(std::move(f));
            return true;
        }
            
        Function<bool(WORD, MathTypes::uint32)> f(this, &Keyboard::OnKeyUp, key_code, char_code);
        events_.push(std::move(f));
        return true;
    }

    if (message == WM_CHAR)
    {
        const WCHAR character = static_cast<WCHAR>(wParam);
        return OnKeyChar(character);
    }
    
    return false;
}

bool Keyboard::OnKeyDown(WORD key_code, MathTypes::uint32 char_code, bool is_repeat)
{
    OnInputKey(key_code, is_repeat ? InputState::kRepeat : InputState::kPressed);
    return true;
}

bool Keyboard::OnKeyUp(WORD key_code, MathTypes::uint32 char_code)
{
    OnInputKey(key_code, InputState::kReleased);
    return true;
}

bool Keyboard::OnKeyChar(WCHAR character)
{
    return true;
}

void Keyboard::OnInputKey(WORD key_code, InputState state)
{
    key_states_[key_code].event_accumulator[static_cast<MathTypes::uint32>(state)];
}
