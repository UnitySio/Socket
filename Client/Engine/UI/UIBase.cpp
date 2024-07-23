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
    anchor_min_({.5f, .5f}),
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

void UIBase::SetAnchors(const Math::Vector2& kAnchorMin, const Math::Vector2& kAnchorMax)
{
    anchor_min_ = kAnchorMin;
    anchor_max_ = kAnchorMax;
    UpdateRect();
}

void UIBase::SetAnchorPreset(MathTypes::uint16 anchor, bool match_pivot)
{
    if ((anchor & kLeft) && (anchor & kTop)) SetAnchors({0.f, 1.f}, {0.f, 1.f});
    else if ((anchor & kRight) && (anchor & kTop)) SetAnchors({1.f, 1.f}, {1.f, 1.f});
    else if ((anchor & kMiddle) && (anchor & kCenter)) SetAnchors({.5f, .5f}, {.5f, .5f});
    else if ((anchor & kLeft) && (anchor & kBottom)) SetAnchors({0.f, 0.f}, {0.f, 0.f});
    else if ((anchor & kRight) && (anchor & kBottom)) SetAnchors({1.f, 0.f}, {1.f, 0.f});
    else if ((anchor & kStretch) && (anchor & kTop)) SetAnchors({0.f, 1.f}, {1.f, 1.f});
    else if ((anchor & kStretch) && (anchor & kCenter)) SetAnchors({0.f, .5f}, {1.f, .5f});
    else if ((anchor & kStretch) && (anchor & kBottom)) SetAnchors({0.f, 0.f}, {1.f, 0.f});
    else if ((anchor & kStretch) && (anchor & kLeft)) SetAnchors({0.f, 0.f}, {0.f, 1.f});
    else if ((anchor & kStretch) && (anchor & kMiddle)) SetAnchors({.5f, 0.f}, {.5f, 1.f});
    else if ((anchor & kStretch) && (anchor & kRight)) SetAnchors({1.f, 0.f}, {1.f, 1.f});
    else if (anchor & kTop) SetAnchors({.5f, 1.f}, {.5f, 1.f});
    else if (anchor & kLeft) SetAnchors({0.f, .5f}, {0.f, .5f});
    else if (anchor & kRight) SetAnchors({1.f, .5f}, {1.f, .5f});
    else if (anchor & kBottom) SetAnchors({.5f, 0.f}, {.5f, 0.f});
    else if (anchor & kStretch) SetAnchors({0.f, 0.f}, {1.f, 1.f});

    if (match_pivot)
    {
        if (anchor & kLeft) pivot_.x = 0.f;
        else if (anchor & kRight) pivot_.x = 1.f;
        else pivot_.x = .5f;

        if (anchor & kTop) pivot_.y = 1.f;
        else if (anchor & kBottom) pivot_.y = 0.f;
        else pivot_.y = .5f;

        UpdateRect();
    }
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

    if (anchor_min_.x == anchor_max_.x)
    {
        left = canvas_width * anchor_min_.x + position_.x;
        right = size_.x;
    }
    else
    {
        left = canvas_width * anchor_min_.x + position_.x;
        right = (anchor_max_.x - anchor_min_.x) * canvas_width - position_.x - size_.x;
    }

    if (anchor_min_.y == anchor_max_.y)
    {
        float anchored_min_y = canvas_height * (1.f - anchor_min_.y);
        if (anchor_min_.y == 0.f) anchored_min_y = canvas_height;
        
        top = anchored_min_y + position_.y;
        bottom = size_.y;
    }
    else
    {
        float anchored_max_y = canvas_height * (1.f - anchor_max_.y);
        if (anchor_max_.y == 0.f) anchored_max_y = 0.f;
        
        top = anchored_max_y + position_.y;
        bottom = (anchor_max_.y - anchor_min_.y) * canvas_height - position_.y - size_.y;
    }
    
    const float pivot_x = right * pivot_.x;
    
    float pivot_y = bottom * pivot_.y;
    if (pivot_y == 0.f) pivot_y = bottom;
    else if (pivot_y == bottom) pivot_y = 0.f;

    if (anchor_min_.x == anchor_max_.x)
    {
        left -= pivot_x;
    }

    if (anchor_min_.y == anchor_max_.y)
    {
        top -= pivot_y;
    }

    rect_ = {left, top, right, bottom};
}
