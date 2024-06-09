#pragma once
#include <Windows.h>

#include "Singleton.h"
#include "Math/MathTypes.h"

enum class InputState
{
    kPressed,
    kReleased,
    kRepeat
};

class Keyboard : public Singleton<Keyboard>
{
public:
    Keyboard();
    virtual ~Keyboard() override = default;

private:
    friend class Core;
    
    bool ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);
    bool OnKeyDown(WORD key_code, MathTypes::uint32 char_code, bool is_repeat);
    bool OnKeyUp(WORD key_code, MathTypes::uint32 char_code);
    bool OnKeyChar(WCHAR character);

    void OnInputKey(WORD key_code, InputState state);
    
};