#include "pch.h"
#include "UIBase.h"

#include "Canvas.h"
#include "Level/World.h"
#include "Math/Color.h"
#include "Math/Rect.h"
#include "Windows/DX/Renderer.h"

UIBase::UIBase() :
    rect_(),
    position_(Math::Vector2::Zero()),
    size_({100.f, 100.f}),
    anchor_min_({0.f, 0.f}),
    anchor_max_({.5f, .5f}),
    pivot_({.5f, .5f})
{
}

void UIBase::SetPosition(const Math::Vector2& kPosition)
{
    position_ = kPosition;
    UpdateRect();
}

void UIBase::SetSize(const Math::Vector2& kSize)
{
    size_ = kSize;
    UpdateRect();
}

void UIBase::SetAnchorMin(const Math::Vector2& kAnchorMin)
{
    anchor_min_ = kAnchorMin;
    UpdateRect();
}

void UIBase::SetAnchorMax(const Math::Vector2& kAnchorMax)
{
    anchor_max_ = kAnchorMax;
    UpdateRect();
}

void UIBase::SetPivot(const Math::Vector2& kPivot)
{
    pivot_ = kPivot;
    UpdateRect();
}

void UIBase::Render()
{
    WindowsWindow* window = World::Get()->GetWindow();
    Renderer::Get()->DrawString(window, L"Hello, World!", rect_, pivot_, Math::Color::White);
    Renderer::Get()->DrawBox(window, rect_, pivot_, Math::Color::Red);
}

void UIBase::UpdateRect()
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
        left = canvas_width * anchor_min_.x + position_.x;
        top = canvas_height * (1.f - anchor_min_.y) - position_.y;
        right = size_.x;
        bottom = size_.y;
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

    rect_ = {left, top, right, bottom};
}
