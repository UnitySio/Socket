#include "Keyboard.h"

#include <ranges>

Keyboard::Keyboard() :
    key_state_map_()
{
    key_state_map_[VK_LEFT] = KeyState();
}

void Keyboard::Tick(float delta_time)
{
    for (auto& val : key_state_map_ | std::views::values)
    {
        const MathTypes::uint32 press_delta = val.event_counts[static_cast<size_t>(InputEvent::kPressed)] - val.event_counts[static_cast<size_t>(InputEvent::kReleased)];
        if (press_delta < 0)
        {
            val.is_down = false;
        }
        else if (press_delta > 0)
        {
            val.is_down = true;
        }
        else
        {
            val.is_down = val.is_previous_down;
        }
    }
    
    for (auto& val : key_state_map_ | std::views::values)
    {
        val.is_previous_down = val.is_down;
    }
    
    // 테스트용 코드
    if (IsKeyPressed(VK_LEFT)) OutputDebugString(L"VK_LEFT is pressed.\n");
    if (IsKeyReleased(VK_LEFT)) OutputDebugString(L"VK_LEFT is released.\n");
    if (IsKeyRepeat(VK_LEFT)) OutputDebugString(L"VK_LEFT is repeated.\n");
}

bool Keyboard::IsKeyPressed(WORD key_code) const
{
    return key_state_map_.at(key_code).is_down && !key_state_map_.at(key_code).is_previous_down;
}

bool Keyboard::IsKeyReleased(WORD key_code) const
{
    return !key_state_map_.at(key_code).is_down && key_state_map_.at(key_code).is_previous_down;
}

bool Keyboard::IsKeyRepeat(WORD key_code) const
{
    return key_state_map_.at(key_code).is_down && key_state_map_.at(key_code).is_previous_down;
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
        
        if (!is_released) return OnKeyDown(key_code, char_code, is_repeat);
        return OnKeyUp(key_code, char_code);
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
    if (is_repeat)
    {
        key_state_map_[key_code].event_counts[static_cast<size_t>(InputEvent::kRepeat)]++;
    }
    else
    {
        key_state_map_[key_code].event_counts[static_cast<size_t>(InputEvent::kPressed)]++;
    }
    
    return true;
}

bool Keyboard::OnKeyUp(WORD key_code, MathTypes::uint32 char_code)
{
    key_state_map_[key_code].event_counts[static_cast<size_t>(InputEvent::kReleased)]++;
    return true;
}

bool Keyboard::OnKeyChar(WCHAR character)
{
    return true;
}
