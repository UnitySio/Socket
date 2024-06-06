#pragma once
#include <Windows.h>

#include <vector>
#include "Singleton.h"
#include "Math/MathTypes.h"
#include "Misc/Delegate.h"

struct EventKeyboard;
//enum class EventKeyboard::Keycode : MathTypes::uint8;

class Keyboard : public Singleton<Keyboard>
{
public:
    Keyboard();
    virtual ~Keyboard() override = default;

    void RegisterKey(BYTE keycode);
    void UnRegisterKey(BYTE keycode);

    Delegate<void(const EventKeyboard& kE)> OnDown;
    Delegate<void(const EventKeyboard& kE)> OnUp;
    Delegate<void(const EventKeyboard& kE)> Pressed;


private:
    bool ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);
    void OnKeyDown(const EventKeyboard& kE);
    void OnKeyUp(const EventKeyboard& kE);
    void Pressing(const EventKeyboard& kE);


    std::vector<EventKeyboard> keys_;
    friend class Core;
};


struct EventKeyboard
{

    enum class KeyState : MathTypes::uint8
    {
        Down,
        Up,
        Pressing
    };

    EventKeyboard(BYTE keycode, WORD keyflag)
        : keyCode_(keycode), keyflag_(keyflag), keyState_(KeyState::Up)
    {};
    
    BYTE keyCode_;
    UINT keyflag_;
    KeyState keyState_;
};