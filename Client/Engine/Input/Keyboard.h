#pragma once
#include <map>
#include <Windows.h>

#include "Singleton.h"
#include "Math/MathTypes.h"

enum class InputState
{
    kPressed,
    kReleased,
    kRepeat,
    kMax
};

struct KeyState
{
    bool is_down;
    bool was_down;

    KeyState() :
        is_down(false),
        was_down(false)
    {
    }
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

    std::map<WORD, KeyState> key_states_;
    
};