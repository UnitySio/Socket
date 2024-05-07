#include "Keyboard.h"

#include <Windows.h>
#include <iostream>

KeyState Keyboard::keys[26];

void Keyboard::Process(MathTypes::uint32 vk_code, bool was_down, bool is_down)
{
    if (was_down == is_down) return;

    WCHAR buffer[256];
    swprintf_s(buffer, L"Key: %d, was_down: %d, is_down: %d\n", vk_code, was_down, is_down);
    OutputDebugString(buffer);

    if (vk_code >= 'A' && vk_code <= 'Z')
    {
        MathTypes::uint32 key_code = vk_code - 'A';
        keys[key_code].is_down = is_down;
        keys[key_code].was_down = was_down;
    }
}

bool Keyboard::IsKeyDown(MathTypes::uint32 key_code)
{
    if (!keys[key_code].was_down && keys[key_code].is_down)
    {
        keys[key_code].was_down = true;
        return true;
    }
    
    return false;
}

bool Keyboard::IsKeyPressed(MathTypes::uint32 key_code)
{
    return keys[key_code].is_down;
}

bool Keyboard::IsKeyUp(MathTypes::uint32 key_code)
{
    if (keys[key_code].was_down && !keys[key_code].is_down)
    {
        keys[key_code].was_down = false;
        return true;
    }
    
    return false;
}
