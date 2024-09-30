#pragma once
#include <queue>

#include "Singleton.h"

#include <Windows.h>

namespace InputSystem
{
    enum class KeyAction
    {
        kPressed,
        kReleased,
        kText
    };
    
    struct KeyEvnet
    {
        KeyAction action;
        WORD key_code;
        WCHAR character;
        bool is_repeat;
    };

    class Keyboard : public Singleton<Keyboard>
    {
    public:
        Keyboard();
        virtual ~Keyboard() override = default;

        bool PollEvents(KeyEvnet& event);
        bool GetKeyState(WORD key_code);

    private:
        friend class Core;
    
        bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);

        std::queue<KeyEvnet> key_events_;

        std::map<WORD, bool> key_states_;

        // 스레드로 부터 안전을 위한 뮤텍스
        std::mutex mutex_;
    
    };
}
