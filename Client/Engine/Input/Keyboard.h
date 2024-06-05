#pragma once
#include <Windows.h>

#include "Singleton.h"
#include "Math/MathTypes.h"

class Keyboard : public Singleton<Keyboard>
{
public:
    Keyboard();
    virtual ~Keyboard() override = default;

    bool ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);

    void OnKeyDown(WPARAM wParam, LPARAM lParam);
    void OnKeyUp(WPARAM wParam, LPARAM lParam);
    
};
