﻿#pragma once
#include <map>
#include <queue>
#include <stack>
#include <Windows.h>

#include "Singleton.h"
#include "Math/MathTypes.h"

#pragma comment(lib, "imm32.lib")

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
    WCHAR character;
};

class Keyboard : public Singleton<Keyboard>
{
public:
    Keyboard();
    virtual ~Keyboard() override = default;

    bool GetKey(WORD key_code);
    bool GetKeyDown(WORD key_code);
    bool GetKeyUp(WORD key_code);

    inline const std::wstring& GetInputString() const { return input_string_; }

private:
    friend class Core;
    friend class GameEngine;
    
    bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);
    bool OnKeyDown(WORD key_code, MathTypes::uint32 char_code);
    bool OnKeyUp(WORD key_code, MathTypes::uint32 char_code);
    bool OnKeyChar(WCHAR character);

    void OnInputKey(WORD key_code, KeyboardEventType state);
    void Begin();
    void End();
    void Clear();

    std::wstring input_string_;

    std::map<WORD, KeyState> key_states_;

    std::queue<KeyEvent> key_events_; 
    
    // 스레드로 부터 안전을 위한 뮤텍스
    std::mutex mutex_;
    
};