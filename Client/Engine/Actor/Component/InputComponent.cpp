#include "InputComponent.h"

#include <Windows.h>

#include "Actor/Actor.h"
#include "Level/World.h"
#include "Windows/WindowsWindow.h"

InputComponent::InputComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    key_states_(),
    mouse_position_(Math::Vector2::Zero())
{
}

void InputComponent::TickComponent(float delta_time)
{
    ActorComponent::TickComponent(delta_time);
    
    for (auto& key_state : key_states_)
    {
        key_state.second.was_down = key_state.second.is_down;
        key_state.second.is_down = GetAsyncKeyState(key_state.first) & 0x8000;
    }

    POINT mouse_pos = {};
    GetCursorPos(&mouse_pos);
    ScreenToClient(World::Get()->GetWindow()->GetHWnd(), &mouse_pos);

    const float mouse_x = static_cast<float>(mouse_pos.x);
    const float mouse_y = static_cast<float>(mouse_pos.y);

    mouse_position_ = { mouse_x, mouse_y };
    
}

void InputComponent::RegisterKey(MathTypes::uint32 key_code)
{
    key_states_[key_code] = KeyState();
}

void InputComponent::UnregisterKey(MathTypes::uint32 key_code)
{
    key_states_.erase(key_code);
}

bool InputComponent::IsKeyDown(MathTypes::uint32 key_code) const
{
    if (key_states_.contains(key_code))
    {
        return key_states_.at(key_code).is_down && !key_states_.at(key_code).was_down;
    }
    
    return false;
}

bool InputComponent::IsKeyUp(MathTypes::uint32 key_code) const
{
    if (key_states_.contains(key_code))
    {
        return !key_states_.at(key_code).is_down && key_states_.at(key_code).was_down;
    }
    
    return false;
}

bool InputComponent::IsKeyPressed(MathTypes::uint32 key_code) const
{
    if (key_states_.contains(key_code))
    {
        return key_states_.at(key_code).is_down;
    }
    
    return false;
}
