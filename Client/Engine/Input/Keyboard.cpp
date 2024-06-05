#include "Keyboard.h"

Keyboard::Keyboard()
{
}

bool Keyboard::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
    if (message == WM_KEYDOWN || message == WM_SYSKEYDOWN ||
        message == WM_KEYUP || message == WM_SYSKEYUP)
    {
        WORD key_code = LOWORD(wParam);
        WORD key_flags = HIWORD(lParam);
        WORD scan_code = LOBYTE(key_flags);

        bool is_down = (key_flags & KF_UP) != KF_UP;
        if (is_down)
        {
            EventKeyboard e(EventKeyboard::Keycode::KEY_0, EventKeyboard::KeyFlag::Down);
            OnKeyDown(e);
        }
        else
        {
            EventKeyboard e(EventKeyboard::Keycode::KEY_0, EventKeyboard::KeyFlag::Up);
            OnKeyUp(e);
        }
        
        return true;
    }
    
    return false;
}

void Keyboard::OnKeyDown(EventKeyboard e)
{
    OnDown.Execute(std::move(e));
}

void Keyboard::OnKeyUp(EventKeyboard e)
{
    OnUp.Execute(std::move(e));
}
