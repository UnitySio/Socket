#include "pch.h"
#include "Gamepad.h"

#include <xinput.h>
#include "Windows.h"

Gamepad::Gamepad()
{
}

void Gamepad::Tick()
{
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    DWORD result = XInputGetState(0, &state);
    if (result == ERROR_SUCCESS)
    {
        // Gamepad is connected
    }
    else
    {
        // Gamepad is not connected
    }
}
