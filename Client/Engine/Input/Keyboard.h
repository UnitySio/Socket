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

    void OnKeyDown(WORD key_code, MathTypes::uint32 char_code, bool is_repeat);
    void OnKeyUp(WORD key_code, MathTypes::uint32 char_code);
    void OnKeyChar(WCHAR character);
    
};