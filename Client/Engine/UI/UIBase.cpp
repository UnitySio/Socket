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
    anchor_min_({0.f, 0.f}),
    anchor_max_({.75f, .75f})
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
    // pivot 왼쪽 상단을 기준

    MathTypes::uint32 canvas_width = Canvas::Get()->width_;
    MathTypes::uint32 canvas_height = Canvas::Get()->height_;

    float left = canvas_width * anchor_min_.x + position_.x;
    float top = canvas_height * (1.f - anchor_max_.y) + position_.y;
    float right = (anchor_max_.x - anchor_min_.x) * canvas_width + size_.x;
    float bottom = (anchor_max_.y - anchor_min_.y) * canvas_height - size_.y - position_.y;

    Math::Rect rect(left, top, right, bottom);

    WindowsWindow* window = World::Get()->GetWindow();
    Renderer::Get()->DrawBox(window, rect, Math::Color::White);
}
