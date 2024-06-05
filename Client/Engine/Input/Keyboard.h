#pragma once
#include <Windows.h>

#include "Singleton.h"
#include "Math/MathTypes.h"
#include "Misc/Delegate.h"

struct EventKeyboard;

class Keyboard : public Singleton<Keyboard>
{
public:
    Keyboard();
    virtual ~Keyboard() override = default;

    bool ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);

    void OnKeyDown(EventKeyboard e);
    void OnKeyUp(EventKeyboard e);
    
    Delegate<void(EventKeyboard e)> OnDown;
    Delegate<void(EventKeyboard e)> OnUp;

};


struct EventKeyboard
{
    enum class Keycode : MathTypes::uint8
    {
        KEY_0,
        KEY_1,
    };

    enum class KeyFlag : MathTypes::uint8
    {
        None,
        Down,
        Up,
        Pressing
    };

    EventKeyboard(Keycode keycode_, KeyFlag KeyFlag_)
        : Keycode(keycode_), KeyFlag(KeyFlag_)
    {};
    
    Keycode Keycode;
    KeyFlag KeyFlag;
};