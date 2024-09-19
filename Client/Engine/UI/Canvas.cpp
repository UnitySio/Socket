#include "pch.h"
#include "Canvas.h"

#include "Widget.h"
#include "Input/Mouse.h"
#include "Widget/Button.h"

Canvas::Canvas() :
    width_(0.f),
    height_(0.f),
    reference_resolution_width_(ProjectSettings::kCanvasReferenceWidth),
    reference_resolution_height_(ProjectSettings::kCanvasReferenceHeight),
    match_mode_(ProjectSettings::kMatchMode),
    widgets_(),
    hovered_widget_(nullptr)
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

void Canvas::OnResize(MathTypes::uint32 width, MathTypes::uint32 height)
{
    width_ = width;
    height_ = height;

    for (const auto& widget : widgets_)
    {
        widget->UpdateRect();
    }
}

void Canvas::Tick()
{
    Mouse* mouse = Mouse::Get();
    if (!mouse) return;

    Math::Vector2 mouse_position = mouse->GetMousePosition();
    
    Widget* hovered_widget = nullptr;
    for (auto it = widgets_.rbegin(); it != widgets_.rend(); ++it)
    {
        Widget* widget = it->get();
        if (widget->rect_.Contains(mouse_position))
        {
            if (dynamic_cast<UI::Button*>(widget))
            {
                if (!hovered_widget || widget->z_index_ > hovered_widget->z_index_)
                {
                    hovered_widget = widget;
                }
            }
        }
    }

    if (hovered_widget_ != hovered_widget)
    {
        if (hovered_widget_) hovered_widget_->OnMouseLeave();
        hovered_widget_ = hovered_widget;
        if (hovered_widget_) hovered_widget->OnMouseHover();
    }

    if (mouse->GetMouseButtonDown(MouseButton::kLeft))
    {
        if (hovered_widget_) hovered_widget_->OnMousePressed();
    }
    else if (mouse->GetMouseButtonUp(MouseButton::kLeft))
    {
        if (hovered_widget_) hovered_widget_->OnMouseReleased();
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
    hovered_widget_ = nullptr;
    widgets_.clear();
}
