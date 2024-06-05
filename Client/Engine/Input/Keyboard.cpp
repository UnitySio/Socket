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
            OnKeyDown(wParam, lParam);
        }
        else
        {
            OnKeyUp(wParam, lParam);
        }
        
        return true;
    }
    
    return false;
}

void Keyboard::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
}

void Keyboard::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
}
