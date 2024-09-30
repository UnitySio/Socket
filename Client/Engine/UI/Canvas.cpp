#include "pch.h"
#include "Canvas.h"

#include "Logger.h"
#include "Widget.h"
#include "Input/InputSystem.h"
#include "Input/Mouse.h"
#include "Widget/Button.h"
#include "Widget/TextBox.h"

Canvas::Canvas() :
    width_(0.f),
    height_(0.f),
    reference_resolution_width_(ProjectSettings::kCanvasReferenceWidth),
    reference_resolution_height_(ProjectSettings::kCanvasReferenceHeight),
    match_mode_(ProjectSettings::kMatchMode),
    widgets_(),
    hovered_widget_(nullptr),
    focused_widget_(nullptr)
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

void Canvas::BeginPlay()
{
    for (const auto& ui : widgets_)
    {
        ui->BeginPlay();
    }
}

void Canvas::Tick(float delta_time)
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
            if (dynamic_cast<UI::Button*>(widget) || dynamic_cast<UI::TextBox*>(widget))
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
        if (hovered_widget_)
        {
            if (hovered_widget_ != focused_widget_)
            {
                if (focused_widget_) focused_widget_->OnBlur();
                focused_widget_ = hovered_widget_;
                focused_widget_->OnFocus();
            }

            hovered_widget_->OnMouseReleased();
        }
        else
        {
            if (focused_widget_)
            {
                focused_widget_->OnBlur();
                focused_widget_ = nullptr;
            }
        }
    }

    InputSystem::Keyboard* keyboard = InputSystem::Keyboard::Get();
    InputSystem::KeyEvnet event;
    while (keyboard->PollEvents(event))
    {
        if (event.action == InputSystem::KeyAction::kPressed)
        {
            if (focused_widget_) focused_widget_->OnKeyEvent(event.key_code, true);
        }
        else if (event.action == InputSystem::KeyAction::kReleased)
        {
            if (focused_widget_) focused_widget_->OnKeyEvent(event.key_code, false);
        }
        else if (event.action == InputSystem::KeyAction::kText)
        {
            if (focused_widget_) focused_widget_->OnCharEvent(event.character);
        }
    }

    for (const auto& ui : widgets_)
    {
        ui->Tick(delta_time);
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
    focused_widget_ = nullptr;
    widgets_.clear();
}
