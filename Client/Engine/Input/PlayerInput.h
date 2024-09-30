#pragma once
#include <map>
#include <Windows.h>

#include "Singleton.h"

struct KeyEvnet;

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

class PlayerInput : public Singleton<PlayerInput>
{
public:
    PlayerInput();
    virtual ~PlayerInput() override = default;

    bool GetKey(WORD key_code);
    bool GetKeyDown(WORD key_code);
    bool GetKeyUp(WORD key_code);

private:
    friend class Core;
    friend class GameEngine;
    
    void OnKeyEvent(const KeyEvnet& kEvent);
    void UpdateKeyStates();
    void Clear();

    std::map<WORD, KeyState> key_states_;
    
    // 스레드로 부터 안전을 위한 뮤텍스
    std::mutex mutex_;
    
};