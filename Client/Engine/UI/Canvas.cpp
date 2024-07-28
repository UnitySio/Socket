#include "pch.h"
#include "Canvas.h"

#include "Widget.h"
#include "Input/Mouse.h"

Canvas::Canvas() :
    width_(0.f),
    height_(0.f),
    reference_resolution_width_(ProjectSettings::kCanvasReferenceWidth),
    reference_resolution_height_(ProjectSettings::kCanvasReferenceHeight),
    match_mode_(ProjectSettings::kMatchMode),
    widgets_()
{
}

void Canvas::AddWidget(const std::shared_ptr<Widget>& kWidget)
{
    widgets_.push_back(kWidget);
}

float Canvas::GetScaleRatio() const
{
    const float width_ratio = width_ / static_cast<float>(reference_resolution_width_);
    const float height_ratio = height_ / static_cast<float>(reference_resolution_height_);

    return width_ratio * (1.f - match_mode_) + height_ratio * match_mode_;
}

Widget* Canvas::GetWidgetAtPosition(const Math::Vector2& kPosition)
{
    Widget* selected_widget = nullptr;
    for (auto it = widgets_.rbegin(); it != widgets_.rend(); ++it)
    {
        Widget* widget = it->get();
        if (widget->rect_.Contains(kPosition))
        {
            if (selected_widget)
            {
                if (widget->z_index_ > selected_widget->z_index_) selected_widget = widget;
            }
            else selected_widget = widget;
        }
    }

    return selected_widget;
}

void Canvas::OnResize(MathTypes::uint32 width, MathTypes::uint32 height)
{
    width_ = width;
    height_ = height;

    for (const auto& ui : widgets_)
    {
        ui->UpdateRect();
    }
}

void Canvas::Tick()
{
    Mouse* mouse = Mouse::Get();
    if (!mouse) return;

    Math::Vector2 mouse_position = mouse->GetMousePosition();

    bool is_mouse_pressed = mouse->IsButtonPressed(MouseButton::kLeft);
    bool is_mouse_released = mouse->IsButtonReleased(MouseButton::kLeft);
    
    if (is_mouse_pressed)
    {
        Widget* selected_widget = GetWidgetAtPosition(mouse_position);
        if (selected_widget) selected_widget->OnMousePressed();
    }
    
    if (is_mouse_released)
    {
        Widget* selected_widget = GetWidgetAtPosition(mouse_position);
        if (selected_widget) selected_widget->OnMouseReleased();
    }
}

void Canvas::Render()
{
    for (const auto& ui : widgets_)
    {
        ui->Render();
    }
}

void Canvas::Clear()
{
    widgets_.clear();
}
