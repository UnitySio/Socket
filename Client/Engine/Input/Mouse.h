#pragma once
#include <queue>
#include <Windows.h>

#include "Singleton.h"
#include "Math/MathTypes.h"
#include "Math/Vector2.h"

enum class MouseEventType
{
    kHWeel,
    kVWheel,
    kMove
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

struct MouseEvent
{
    MouseEventType type;

    int wheel_delta;
    
    Math::Vector2 mouse_position;

    MouseEvent() :
        type(MouseEventType::kMove),
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

    inline int GetScrollX() const { return scroll_x_; }
    inline int GetScrollY() const { return scroll_y_; }
    
    inline Math::Vector2 GetMousePosition() const { return mouse_position_; }

private:
    friend class Core;
    friend class GameEngine;
    
    bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);

    void Begin();
    void End();
    void Clear();

    std::queue<MouseEvent> mouse_events_;

    int scroll_x_;
    int scroll_y_;
    
    Math::Vector2 mouse_position_;

    // 스레드로 부터 안전을 위한 뮤텍스
    std::mutex mutex_;
    
};
