#include "InputManager.h"

#include "../Core.h"
#include "../Enums.h"

InputManager::InputManager()
{
}

void InputManager::Init()
{
    key_map_[VK_UP] = Key();
    key_map_[VK_DOWN] = Key();
    key_map_[VK_LEFT] = Key();
    key_map_[VK_RIGHT] = Key();
    key_map_[VK_SPACE] = Key();
}

void InputManager::Tick()
{
    for (auto& key : key_map_)
    {
        if (Core::GetInstance()->GetFocusHandle())
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
