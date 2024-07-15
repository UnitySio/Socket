#include "pch.h"
#include "Mouse.h"

#include <windowsx.h>

#include "Logger/Logger.h"

Mouse::Mouse() :
    mouse_states_{},
    mouse_events_(),
    wheel_axis_(0),
    wheel_h_axis_(0),
    mouse_position_(Math::Vector2::Zero())
{
}

bool Mouse::IsButtonDown(MouseButton button) const
{
    MouseState state = mouse_states_[static_cast<int>(button)];
    return state.is_down && state.was_down;
}

bool Mouse::IsButtonPressed(MouseButton button) const
{
    MouseState state = mouse_states_[static_cast<int>(button)];
    return state.is_down && !state.was_down;
}

bool Mouse::IsButtonReleased(MouseButton button) const
{
    MouseState state = mouse_states_[static_cast<int>(button)];
    return !state.is_down && state.was_down;
}

bool Mouse::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
    if (message == WM_LBUTTONDOWN ||
        message == WM_LBUTTONUP ||
        message == WM_RBUTTONDOWN ||
        message == WM_RBUTTONUP ||
        message == WM_MBUTTONDOWN ||
        message == WM_MBUTTONUP)
    {
        MouseButton mouse_button = MouseButton::kNone;
        bool is_released = false;

        switch (message)
        {
        case WM_LBUTTONDOWN:
            {
                mouse_button = MouseButton::kLeft;
            }
            break;

        case WM_LBUTTONUP:
            {
                mouse_button = MouseButton::kLeft;
                is_released = true;
            }
            break;

        case WM_RBUTTONDOWN:
            {
                mouse_button = MouseButton::kRight;
            }
            break;

        case WM_RBUTTONUP:
            {
                mouse_button = MouseButton::kRight;
                is_released = true;
            }
            break;

        case WM_MBUTTONDOWN:
            {
                mouse_button = MouseButton::kMiddle;
            }
            break;

        case WM_MBUTTONUP:
            {
                mouse_button = MouseButton::kMiddle;
                is_released = true;
            }
            break;
        }

        ButtonEvent event;
        event.type = is_released ? MouseEventType::kReleased : MouseEventType::kPressed;
        event.button = mouse_button;

        mouse_events_.push(event);
        return true;
    }

    if (message == WM_MOUSEWHEEL)
    {
        const int z_delta = GET_WHEEL_DELTA_WPARAM(wParam);

        ButtonEvent event;
        event.type = MouseEventType::kWheel;
        event.wheel_delta = z_delta / WHEEL_DELTA;

        mouse_events_.push(event);
        return true;
    }

    if (message == WM_MOUSEHWHEEL)
    {
        const int z_delta = GET_WHEEL_DELTA_WPARAM(wParam);

        ButtonEvent event;
        event.type = MouseEventType::kHWeel;
        event.wheel_delta = z_delta / WHEEL_DELTA;

        mouse_events_.push(event);
        return true;
    }

    if (message == WM_MOUSEMOVE)
    {
        const int x = GET_X_LPARAM(lParam);
        const int y = GET_Y_LPARAM(lParam);

        ButtonEvent event;
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
        ButtonEvent& event = mouse_events_.front();
        mouse_events_.pop();

        MouseEventType type = event.type;

        switch (type)
        {
        case MouseEventType::kPressed:
            {
                mouse_states_[static_cast<int>(event.button)].is_down = true;
            }
            break;

        case MouseEventType::kReleased:
            {
                mouse_states_[static_cast<int>(event.button)].is_down = false;
            }
            break;

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
    for (auto& mouse_state : mouse_states_)
    {
        mouse_state.was_down = mouse_state.is_down;
    }

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

    for (auto& mouse_state : mouse_states_)
    {
        mouse_state.is_down = false;
        mouse_state.was_down = false;
    }

    wheel_axis_ = 0;
    wheel_h_axis_ = 0;
}
