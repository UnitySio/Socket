﻿#include "pch.h"
#include "EventManager.h"

#include <windowsx.h>

#include "Input/Mouse.h"

EventManager::EventManager() :
    events_()
{
}

bool EventManager::PollEvent(Event& event)
{
    if (events_.empty()) return false;

    event = events_.front();
    events_.pop();

    return true;
}

bool EventManager::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
    if (message == WM_SIZE)
    {
        if (wParam == SIZE_MINIMIZED) return false;

        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        
        Event event;
        event.type = EventType::kWindowSize;
        event.window.data1 = width;
        event.window.data2 = height;

        events_.push(event);
        return true;
    }
    
    if (message == WM_KEYDOWN || message == WM_SYSKEYDOWN ||
        message == WM_KEYUP || message == WM_SYSKEYUP)
    {
        WORD key_code = LOWORD(wParam);
        WORD key_flags = HIWORD(lParam);
        
        MathTypes::uint32 scancode =  MapVirtualKey(key_code, MAPVK_VK_TO_CHAR);

        bool is_released = (key_flags & KF_UP) == KF_UP;
        bool is_repeat = (key_flags & KF_REPEAT) == KF_REPEAT;

        MathTypes::uint32 type = 0;
        if (!is_released) type = EventType::kKeyPressed;
        else type = EventType::kKeyReleased;

        Event event;
        event.type = type;
        event.key.key_code = key_code;
        event.key.is_repeat = is_repeat;

        events_.push(event);
        return true;
    }
    
    if (message == WM_CHAR)
    {
        const WCHAR kCharacter = static_cast<WCHAR>(wParam);
        if (kCharacter < 32 || (kCharacter > 126 && kCharacter < 160)) return false;

        Event event;
        event.type = EventType::kText;
        event.text.character = kCharacter;

        events_.push(event);
        return true;
    }
    
    if (message == WM_LBUTTONDOWN || message == WM_LBUTTONUP ||
        message == WM_RBUTTONDOWN || message == WM_RBUTTONUP ||
        message == WM_MBUTTONDOWN || message == WM_MBUTTONUP)
    {
        bool is_pressed = false;
        MouseButton mouse_button = MouseButton::kLeft;
        MathTypes::uint32 type = 0;
        
        if ((wParam & MK_LBUTTON))
        {
            is_pressed = true;
            mouse_button = MouseButton::kLeft;
        }
        else if ((wParam & MK_RBUTTON))
        {
            is_pressed = true;
            mouse_button = MouseButton::kRight;
        }
        else if ((wParam & MK_MBUTTON))
        {
            is_pressed = true;
            mouse_button = MouseButton::kMiddle;
        }

        if (is_pressed) type = EventType::kMousePressed;
        else type = EventType::kMouseReleased;

        Event event;
        event.type = type;
        event.button.is_pressed = is_pressed;
        event.button.button = mouse_button;

        events_.push(event);
        return true;
    }

    if (message == WM_MOUSEMOVE)
    {
        const int x = GET_X_LPARAM(lParam);
        const int y = GET_Y_LPARAM(lParam);

        Event event;
        event.type = EventType::kMouseMotion;
        event.motion.x = static_cast<float>(x);
        event.motion.y = static_cast<float>(y);

        events_.push(event);
        return true;
    }

    if (message == WM_MOUSEWHEEL || message == WM_MOUSEHWHEEL)
    {
        const short delta = GET_WHEEL_DELTA_WPARAM(wParam);
        float delta_f = static_cast<float>(delta) / static_cast<float>(WHEEL_DELTA);

        Event event;
        event.type = EventType::kMouseWheel;

        if (message == WM_MOUSEWHEEL)
        {
            event.wheel.x = 0.f;
            event.wheel.y = delta_f;
        }
        else
        {
            event.wheel.x = delta_f;
            event.wheel.y = 0.f;
        }

        events_.push(event);
        return true;
    }
    
    return false;
}

void EventManager::Clear()
{
    events_ = std::queue<Event>();
}
