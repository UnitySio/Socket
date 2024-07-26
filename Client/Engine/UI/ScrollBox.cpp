#include "pch.h"
#include "ScrollBox.h"

#include "Canvas.h"
#include "Input/Mouse.h"
#include "Level/World.h"
#include "Math/Color.h"
#include "Math/Math.h"
#include "Windows/DX/Renderer.h"

UI::ScrollBox::ScrollBox(const std::wstring& kName) :
    UIBase(kName),
    content_rect_(),
    scroll_bar_(),
    scroll_bar_thumb_(),
    is_dragging_(false),
    scroll_offset_(0.f)
{
}

void UI::ScrollBox::Tick(float deltaTime)
{
    UIBase::Tick(deltaTime);

    Canvas* canvas = Canvas::Get();

    scroll_bar_.x = rect_.x + rect_.width - 20.f * canvas->GetScaleRatio();
    scroll_bar_.y = rect_.y;
    scroll_bar_.width = 20.f * canvas->GetScaleRatio();
    scroll_bar_.height = rect_.height;

    content_rect_.x = rect_.x;
    content_rect_.y = rect_.y;
    content_rect_.width = rect_.width - 20.f * canvas->GetScaleRatio();
    content_rect_.height = 300.f * canvas->GetScaleRatio();

    if (content_rect_.height > rect_.height)
    {
        scroll_bar_thumb_.height = rect_.height * (rect_.height / content_rect_.height);
    }
    else
    {
        scroll_bar_thumb_.height = rect_.height;
    }

    Mouse* mouse = Mouse::Get();
    Math::Vector2 mouse_position = mouse->GetMousePosition();
    Math::Vector2 mouse_delta = mouse->GetMouseDelta();

    bool is_pressed = mouse->IsButtonPressed(MouseButton::kLeft);
    bool is_released = mouse->IsButtonReleased(MouseButton::kLeft);

    if (scroll_bar_thumb_.Contains(mouse_position) && is_pressed)
    {
        is_dragging_ = true;
    }
    else if (is_released)
    {
        is_dragging_ = false;
    }

    if (is_dragging_)
    {
        scroll_offset_ += mouse_delta.y;
        scroll_offset_ = Math::Clamp(scroll_offset_, 0.f, scroll_bar_.height - scroll_bar_thumb_.height);
    }

    int wheel_axis = mouse->GetWheelAxis();
    if (rect_.Contains(mouse_position) && wheel_axis != 0)
    {
        scroll_offset_ -= wheel_axis * 10.f;
        scroll_offset_ = Math::Clamp(scroll_offset_, 0.f, scroll_bar_.height - scroll_bar_thumb_.height);
    }

    scroll_bar_thumb_.x = scroll_bar_.x;
    scroll_bar_thumb_.y = scroll_bar_.y + scroll_offset_;
    scroll_bar_thumb_.width = scroll_bar_.width;

    content_rect_.y = rect_.y - scroll_offset_ * (content_rect_.height / rect_.height);

}

void UI::ScrollBox::Render()
{
    WindowsWindow* window = World::Get()->GetWindow();
    Renderer* renderer = Renderer::Get();

    renderer->DrawBox(window, rect_, pivot_, Math::Color::Black);
    renderer->DrawBox(window, content_rect_, pivot_, Math::Color::White);
    
    renderer->BeginLayer(rect_);
    UIBase::Render();
    renderer->EndLayer();

    renderer->DrawBox(window, scroll_bar_, {0.f, 1.f}, {100, 100, 100, 255});
    renderer->DrawBox(window, scroll_bar_thumb_, {0.f, 1.f}, {150, 150, 150, 255});
}
