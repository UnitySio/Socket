#include "pch.h"
#include "UIBase.h"

#include "Canvas.h"
#include "Level/World.h"
#include "Math/Color.h"
#include "Math/Rect.h"
#include "Windows/DX/Renderer.h"

UIBase::UIBase() :
    position_(Math::Vector2::Zero()),
    size_(Math::Vector2::Zero()),
    anchor_min_({.25f, .25f}),
    anchor_max_({.25f, .25f}),
    pivot_({.25f, .5f})
{
}

void UIBase::SetPosition(const Math::Vector2& position)
{
    position_ = position;
}

void UIBase::SetSize(const Math::Vector2& size)
{
    size_ = size;
}

void UIBase::Render()
{
    Canvas* canvas = Canvas::Get();
    MathTypes::uint32 canvas_width = canvas->width_;
    MathTypes::uint32 canvas_height = canvas->height_;

    float left = 0.f;
    float top = 0.f;
    float right = 0.f;
    float bottom = 0.f;

    if (anchor_min_ == anchor_max_)
    {
        right = size_.x;
        bottom = size_.y;
        left = canvas_width * anchor_min_.x + position_.x;
        top = canvas_height * (1.f - anchor_min_.y) - position_.y;
    }
    else
    {
        left = canvas_width * anchor_min_.x + position_.x;
        top = canvas_height * (1.f - anchor_max_.y) + position_.y;
        right = (anchor_max_.x - anchor_min_.x) * canvas_width - position_.x - size_.x;
        bottom = (anchor_max_.y - anchor_min_.y) * canvas_height - position_.y - size_.y;
    }
    
    const float pivot_x = right * pivot_.x;
    const float pivot_y = bottom * pivot_.y;

    if (anchor_min_ == anchor_max_)
    {
        left -= pivot_x;
        top -= pivot_y;
    }

    Math::Rect rect(left, top, right, bottom);

    WindowsWindow* window = World::Get()->GetWindow();
    Renderer::Get()->DrawBox(window, rect, pivot_, Math::Color::White);
}
