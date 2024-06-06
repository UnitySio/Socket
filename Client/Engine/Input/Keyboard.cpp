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
        
        MathTypes::uint32 char_code =  MapVirtualKey(key_code, MAPVK_VK_TO_CHAR);

        bool is_released = (key_flags & KF_UP) == KF_UP;
        bool is_repeat = (key_flags & KF_REPEAT) == KF_REPEAT;
        
        if (!is_released) OnKeyDown(key_code, char_code, is_repeat);
        else OnKeyUp(key_code, char_code);
        
        return true;
    }

    if (message == WM_CHAR)
    {
        const WCHAR character = static_cast<WCHAR>(wParam);
        OnKeyChar(character);
        
        return true;
    }
    
    return false;
}

void Keyboard::OnKeyDown(WORD key_code, MathTypes::uint32 char_code, bool is_repeat)
{
}

void Keyboard::OnKeyUp(WORD key_code, MathTypes::uint32 char_code)
{
}

void Keyboard::OnKeyChar(WCHAR character)
{
}
