#include "Keyboard.h"

#include <Windows.h>

Keyboard::Keyboard()
{
}

void Keyboard::BindAction(MathTypes::uint32 key, Action action)
{
    actions_[key] = action;
}

void Keyboard::Tick()
{
    for (auto& action : actions_)
    {
        if (GetAsyncKeyState(action.first) & 0x8000)
        {
            if (action.second.is_down)
                action.second.Ongoing();
            else action.second.Started();
            
            action.second.is_down = true;
        }
        else
        {
            if (action.second.is_down)
                action.second.Canceled();
            
            action.second.is_down = false;
        }
    }
}
