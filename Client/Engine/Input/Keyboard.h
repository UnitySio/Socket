#pragma once
#include <map>
#include <queue>
#include <Windows.h>

#include "Singleton.h"
#include "Math/MathTypes.h"

enum class InputState
{
    kPressed,
    kReleased,
    kRepeat
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

struct KeyEvent
{
    InputState state;
    WORD key_code;
};

class Keyboard : public Singleton<Keyboard>
{
public:
    Keyboard();
    virtual ~Keyboard() override = default;

    void RegisterKey(WORD key_code);

    bool IsKeyDown(WORD key_code) const;
    bool IsKeyPressed(WORD key_code) const;
    bool IsKeyReleased(WORD key_code) const;

private:
    friend class Core;
    friend class GameEngine;
    
    bool ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);
    bool OnKeyDown(WORD key_code, MathTypes::uint32 char_code, bool is_repeat);
    bool OnKeyUp(WORD key_code, MathTypes::uint32 char_code);
    bool OnKeyChar(WCHAR character);

    void OnInputKey(WORD key_code, InputState state);
    void Begin();
    void End();
    void Clear();

    std::map<WORD, KeyState> key_states_;

    std::queue<KeyEvent> key_events_;

    // 스레드로 부터 안전을 위한 뮤텍스
    std::mutex mutex_;
    
};