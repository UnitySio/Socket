#include "pch.h"
#include "UIBase.h"

#include "Canvas.h"
#include "Input/Mouse.h"
#include "Level/World.h"
#include "Math/Color.h"
#include "Math/Rect.h"

UIBase::UIBase(const std::wstring& kName) :
    name_(kName),
    rect_(),
    position_(Math::Vector2::Zero()),
    size_({100.f, 100.f}),
    anchor_min_({.5f, .5f}),
    anchor_max_({.5f, .5f}),
    pivot_({.5f, .5f}),
    parent_(nullptr),
    children_(),
    is_clicked_(false)
{
    UpdateRect();
}

void UIBase::SetPosition(const Math::Vector2& kPosition)
{
    position_ = kPosition;
    UpdateRect();
}

void UIBase::SetPositionScreen(const Math::Vector2& kPosition)
{
    Canvas* canvas = Canvas::Get();
    const MathTypes::uint32 canvas_width = canvas->width_;
    const MathTypes::uint32 canvas_height = canvas->height_;

    const float scale_ratio = canvas->GetScaleRatio();

    float x = (kPosition.x - canvas_width * anchor_min_.x) / scale_ratio;
    float y = (kPosition.y - canvas_height * (1.f - anchor_min_.y)) / scale_ratio;
    position_ = {x, y};
    
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

void UIBase::AttachToUI(UIBase* parent)
{
    parent_ = parent;
    parent_->children_.push_back(this);
    UpdateRect();
}

void UIBase::DetachFromUI()
{
    if (!parent_) return;

    std::erase(parent_->children_, this);
    parent_ = nullptr;
}

void UIBase::Translate(const Math::Vector2& kTranslation)
{
    position_ += kTranslation;
    UpdateRect();
}

void UIBase::Tick(float deltaTime)
{
    Mouse* mouse = Mouse::Get();
    Math::Vector2 mouse_position = mouse->GetMousePosition();

    if (rect_.Contains(mouse_position) && mouse->IsButtonPressed(MouseButton::kLeft))
    {
        is_clicked_ = true;
    }
    else if (is_clicked_ && mouse->IsButtonReleased(MouseButton::kLeft))
    {
        is_clicked_ = false;
    }
    
    for (UIBase* child : children_)
    {
        child->Tick(deltaTime);
    }
}

void UIBase::Render()
{
    for (UIBase* child : children_)
    {
        child->Render();
    }
}

void UIBase::UpdateRect()
{
    MathTypes::uint32 parent_width = 0;
    MathTypes::uint32 parent_height = 0;
    Math::Vector2 parent_position = {0.f, 0.f};

    Canvas* canvas = Canvas::Get();
    const float scale_ratio = canvas->GetScaleRatio();

    if (parent_)
    {
        parent_width = parent_->rect_.width;
        parent_height = parent_->rect_.height;
        parent_position = {parent_->rect_.x, parent_->rect_.y};
    }
    else
    {
        Canvas* canvas = Canvas::Get();
        parent_width = canvas->width_;
        parent_height = canvas->height_;
    }

    float left = 0.f;
    float top = 0.f;
    float right = 0.f;
    float bottom = 0.f;

    if (anchor_min_.x == anchor_max_.x)
    {
        left = parent_width * anchor_min_.x + position_.x * scale_ratio + parent_position.x;
        right = size_.x * scale_ratio;
    }
    else
    {
        left = parent_width * anchor_min_.x + position_.x * scale_ratio + parent_position.x;
        right = (anchor_max_.x - anchor_min_.x) * parent_width - position_.x * scale_ratio - size_.x;
    }

    if (anchor_min_.y == anchor_max_.y)
    {
        float anchored_min_y = parent_height * (1.f - anchor_min_.y) + parent_position.y;
        if (anchor_min_.y == 0.f) anchored_min_y = parent_height + parent_position.y;

        top = anchored_min_y + position_.y * scale_ratio;
        bottom = size_.y * scale_ratio;
    }
    else
    {
        float anchored_max_y = parent_height * (1.f - anchor_max_.y) + parent_position.y;
        if (anchor_max_.y == 0.f) anchored_max_y = 0.f + parent_position.y;

        top = anchored_max_y + position_.y * scale_ratio;
        bottom = (anchor_max_.y - anchor_min_.y) * parent_height - position_.y * scale_ratio - size_.y * scale_ratio;
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

    for (UIBase* child : children_)
    {
        child->UpdateRect();
    }
}
