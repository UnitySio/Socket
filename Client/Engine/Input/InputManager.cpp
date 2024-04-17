#include "InputManager.h"

#include "Core.h"
#include "Enums.h"

InputManager::InputManager() :
    key_map_(),
    mouse_position_(b2Vec2_zero),
    mouse_previous_position_(b2Vec2_zero),
    mouse_delta_(b2Vec2_zero)
{
}

void InputManager::Init()
{
    key_map_[VK_UP] = Key();
    key_map_[VK_DOWN] = Key();
    key_map_[VK_LEFT] = Key();
    key_map_[VK_RIGHT] = Key();
    key_map_[VK_SPACE] = Key();
    key_map_[VK_F1] = Key();
    key_map_[VK_F2] = Key();
    key_map_[MK_LBUTTON] = Key();
    key_map_[0x57] = Key(); // W
    key_map_[0x41] = Key(); // A
    key_map_[0x53] = Key(); // S
    key_map_[0x44] = Key(); // D
}

void InputManager::Tick()
{
    Core* core = Core::Get();
    
    for (auto& key : key_map_)
    {
        if (core->GetFocusHandle())
        {
            if (GetAsyncKeyState(key.first) & 0x8000)
            {
                if (key.second.is_down)
                    key.second.state = KeyState::kPressed;
                else key.second.state = KeyState::kDown;
                
                key.second.is_down = true;
            }
            else
            {
                if (key.second.is_down)
                    key.second.state = KeyState::kUp;
                else key.second.state = KeyState::kNone;
                
                key.second.is_down = false;
            }
        }
        else
        {
            if (key.second.state == KeyState::kDown || key.second.state == KeyState::kPressed)
                key.second.state = KeyState::kUp;
            else key.second.state = KeyState::kNone;

            key.second.is_down = false;
        }
    }

    if (core->GetFocusHandle())
    {
        POINT mouse_position;
        GetCursorPos(&mouse_position);
        ScreenToClient(core->GetFocusHandle(), &mouse_position);

        mouse_position_.Set(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));
        mouse_delta_ = mouse_position_ - mouse_previous_position_;
        mouse_previous_position_ = mouse_position_;
    }
    else
    {
        mouse_position_.SetZero();
        mouse_previous_position_.SetZero();
        mouse_delta_.SetZero();
    }
}

bool InputManager::IsKeyDown(int key) const
{
    return key_map_.at(key).state == KeyState::kDown;
}

bool InputManager::IsKeyPressed(int key) const
{
    return key_map_.at(key).state == KeyState::kPressed;
}

bool InputManager::IsKeyUp(int key) const
{
    return key_map_.at(key).state == KeyState::kUp;
}
