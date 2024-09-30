#pragma once
#include <map>
#include <queue>
#include <Windows.h>

#include "Singleton.h"
#include "Math/MathTypes.h"

enum class KeyboardEventType
{
    kDown,
    kUp,
    kChar
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
    KeyboardEventType state;
    WORD key_code;
};

class Keyboard : public Singleton<Keyboard>
{
public:
    Keyboard();
    virtual ~Keyboard() override = default;

    bool GetKey(WORD key_code);
    bool GetKeyDown(WORD key_code);
    bool GetKeyUp(WORD key_code);

private:
    friend class Core;
    friend class GameEngine;
    
    bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);
    bool OnKeyDown(WORD key_code, MathTypes::uint32 char_code, bool is_repeat);
    bool OnKeyUp(WORD key_code, MathTypes::uint32 char_code);

    void OnInputKey(WORD key_code, KeyboardEventType state);
    void Begin();
    void End();
    void Clear();

    std::map<WORD, KeyState> key_states_;

    std::queue<KeyEvent> key_events_; 
    
    // 스레드로 부터 안전을 위한 뮤텍스
    std::mutex mutex_;
    
};