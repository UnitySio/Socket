#include "Keyboard.h"

#include <ranges>
#include <Windows.h>

Keyboard::Keyboard()
{
}

void Keyboard::Tick()
{
    for (auto& key_state : key_states_)
    {
        key_state.second.was_down = key_state.second.is_down;
        key_state.second.is_down = GetAsyncKeyState(key_state.first) & 0x8000;
    }
}

void Keyboard::RegisterKey(MathTypes::uint32 key_code)
{
    key_states_[key_code] = KeyState();
}

void Keyboard::UnregisterKey(MathTypes::uint32 key_code)
{
    key_states_.erase(key_code);
}

bool Keyboard::IsKeyDown(MathTypes::uint32 key_code) const
{
    if (key_states_.contains(key_code))
    {
        return key_states_.at(key_code).is_down && !key_states_.at(key_code).was_down;
    }
    
    return false;
}

bool Keyboard::IsKeyUp(MathTypes::uint32 key_code) const
{
    if (key_states_.contains(key_code))
    {
        return !key_states_.at(key_code).is_down && key_states_.at(key_code).was_down;
    }
    
    return false;
}

bool Keyboard::IsKeyPressed(MathTypes::uint32 key_code) const
{
    if (key_states_.contains(key_code))
    {
        return key_states_.at(key_code).is_down;
    }
    
    return false;
}
