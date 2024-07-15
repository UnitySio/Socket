#pragma once
#include <queue>
#include <Windows.h>

#include "Singleton.h"
#include "Math/MathTypes.h"
#include "Math/Vector2.h"

enum class MouseEventType
{
    kPressed,
    kReleased,
    kWheel,
    kHWeel,
    kMove
};

enum class MouseButton
{
    kLeft,
    kRight,
    kMiddle,
    kNone
};

struct MouseState
{
    bool is_down;
    bool was_down;

    MouseState() :
        is_down(false),
        was_down(false)
    {
    }
};

struct ButtonEvent
{
    MouseEventType type;
    MouseButton button;

    int wheel_delta;
    
    Math::Vector2 mouse_position;

    ButtonEvent() :
        type(MouseEventType::kMove),
        button(MouseButton::kNone),
        wheel_delta(0),
        mouse_position(Math::Vector2::Zero())
    {
    }
};

class Mouse : public Singleton<Mouse>
{
public:
    Mouse();
    virtual ~Mouse() override = default;

    bool IsButtonDown(MouseButton button) const;
    bool IsButtonPressed(MouseButton button) const;
    bool IsButtonReleased(MouseButton button) const;

    inline int GetWheelAxis() const { return wheel_axis_; }
    inline int GetWheelHAxis() const { return wheel_h_axis_; }
    
    inline Math::Vector2 GetMousePosition() const { return mouse_position_; }

private:
    friend class Core;
    friend class GameEngine;
    
    bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);

    void Begin();
    void End();
    void Clear();

    MouseState mouse_states_[static_cast<int>(MouseButton::kNone)];

    std::queue<ButtonEvent> mouse_events_;

    int wheel_axis_;
    int wheel_h_axis_;
    
    Math::Vector2 mouse_position_;

    // 스레드로 부터 안전을 위한 뮤텍스
    std::mutex mutex_;
    
};
