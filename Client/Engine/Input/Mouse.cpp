#include "pch.h"
#include "Mouse.h"

#include <windowsx.h>

#include "Logger/Logger.h"

Mouse::Mouse() :
    mouse_events_(),
    wheel_axis_(0),
    wheel_h_axis_(0),
    mouse_position_(Math::Vector2::Zero())
{
}

bool Mouse::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
    if (message == WM_MOUSEWHEEL)
    {
        const int z_delta = GET_WHEEL_DELTA_WPARAM(wParam);

        MouseEvent event;
        event.type = MouseEventType::kWheel;
        event.wheel_delta = z_delta / WHEEL_DELTA;
        
        mouse_events_.push(event);
        return true;
    }
    
    if (message == WM_MOUSEHWHEEL)
    {
        const int z_delta = GET_WHEEL_DELTA_WPARAM(wParam);

        MouseEvent event;
        event.type = MouseEventType::kHWeel;
        event.wheel_delta = z_delta / WHEEL_DELTA;
        
        mouse_events_.push(event);
        return true;
    }
    
    if (message == WM_MOUSEMOVE)
    {
        const int x = GET_X_LPARAM(lParam);
        const int y = GET_Y_LPARAM(lParam);

        MouseEvent event;
        event.type = MouseEventType::kMove;
        event.mouse_position = Math::Vector2(static_cast<float>(x), static_cast<float>(y));

        mouse_events_.push(event);
        return true;
    }
    
    return false;
}

void Mouse::Begin()
{
	std::lock_guard<std::mutex> lock(mutex_);

    while (!mouse_events_.empty())
    {
        MouseEvent& event = mouse_events_.front();
        mouse_events_.pop();

        MouseEventType type = event.type;

        switch (type)
        {
        case MouseEventType::kWheel:
            {
                wheel_axis_ = event.wheel_delta;
            }
            break;
            
        case MouseEventType::kHWeel:
            {
                wheel_h_axis_ = event.wheel_delta;
            }
            break;
            
        case MouseEventType::kMove:
            {
                mouse_position_ = event.mouse_position;
            }
            break;
        }
    }
}

void Mouse::End()
{
    wheel_axis_ = 0;
    wheel_h_axis_ = 0;
}

void Mouse::Clear()
{
	std::lock_guard<std::mutex> lock(mutex_);

    while (!mouse_events_.empty())
    {
        mouse_events_.pop();
    }

    wheel_axis_ = 0;
    wheel_h_axis_ = 0;
}
