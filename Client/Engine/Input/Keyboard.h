#pragma once
#include <map>
#include <Windows.h>

#include "Singleton.h"

union Event;

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

    bool GetKey(WORD key_code);
    bool GetKeyDown(WORD key_code);
    bool GetKeyUp(WORD key_code);

private:
    friend class Core;
    
    void OnKeyEvent(const Event& kEvent);
    void UpdateKeyStates();
    void Clear();

    std::map<WORD, KeyState> key_states_;
    
    // 스레드로 부터 안전을 위한 뮤텍스
    std::mutex mutex_;
    
};