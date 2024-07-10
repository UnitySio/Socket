#include "UIBase.h"
#include <d3d11.h>
#include <wrl.h>
#include <d2d1.h>
#include "../Engine/Windows/DX/Renderer.h"
#include <Windows.h>
#include "Canvas.h"
#include "Misc/Function.h"


UIBase::UIBase()
    :
    position_(Math::Vector2(0, 0)),
    color_(Math::Color(255, 255, 255, 255)),
    offset_(Math::Vector2(0, 0)),
    rotation_(0),
    parentRectsize_(800, 600),
    rectsize_(0, 0),
    parent_(nullptr),
    stroke_(1.0f),
    anchorType_(AnchorType::None),
    isEnabled_(false)
{
    
}

void UIBase::SetParent(UIBase* parent)
{
	parent->children_.push_back(this);
	parent_ = parent;
    parentRectsize_ = parent->rectsize_;
}

void UIBase::SetSize(const Math::Vector2& value)
{
    rectsize_ = value;
    if (!children_.empty())
    {
        for (auto& temp : children_)
        {
            temp->SetSize(value);
        }
    }
}

void UIBase::SetPosition(const Math::Vector2& pos)
{
    position_ = pos;
    /*if (!children_.empty())
    {
        for(const auto& temp : children_)
            
    }*/
}

void UIBase::SetOffset(const Math::Vector2& pos)
{
    offset_ = pos;
}

const Math::Vector2 UIBase::GetPosition()
{
    if (parent_)
        return offset_ + anchor_ + position_ + parent_->GetPosition() + parent_->anchor_;
    return position_;
}

void UIBase::SetAnchorType(const AnchorType& type)
{
    anchorType_ = type;
    RefreshAnchorPos();
}

void UIBase::SetEnable(const bool& flag)
{
    isEnabled_ = flag;
}

void UIBase::SetVisibility(const bool& flag)
{
    isVisible_ = flag;
}

void UIBase::BindAction(const EventType& type, Function<void(void)>&& func)
{
    switch (type)
    {
    case EventType::OnClicked:
    {
        onClickedFunc_ = std::make_shared<Function<void(void)>>(std::forward<Function<void(void)>>(func));
        break;
    }

    case EventType::OnReleased:
    {
        onReleasedFunc_ = std::make_shared<Function<void(void)>>(std::forward<Function<void(void)>>(func));
        break;
    }

    case EventType::Pressing:
    {
        pressingFunc_ = std::make_shared<Function<void(void)>>(std::forward<Function<void(void)>>(func));
        break;
    }
    }
}

void UIBase::SetColor(const Math::Color& kColor)
{
    color_ = kColor;
}

void UIBase::Tick()
{
    if (isDown_ == Canvas::Get()->IsDown())
    {
        onClicked_ = false;
        onReleased_ = false;
        if (isDown_ && pressingFunc_)
            (*pressingFunc_)();
    }
    else if (isDown_ != Canvas::Get()->IsDown())
    {
        if (isDown_)
        {
            isDown_ = Canvas::Get()->IsDown();
            onReleased_ = true;
            pressed_ = false;
            if (onReleasedFunc_)
                (*onReleasedFunc_)();
        }
        else if (!isDown_)
        {
            isDown_ = Canvas::Get()->IsDown();
            onClicked_ = true;
            released_ = false;
            if (onClickedFunc_ && onMouse_)
                (*onClickedFunc_)();
        }
    }
}

void UIBase::Render(WindowsWindow* kWindow)
{
    if (!parent_)
    {
        Viewport* viewport = Renderer::Get()->FindViewport(World::Get()->GetWindow());
        parentRectsize_.x = viewport->d3d_viewport.Width;
        parentRectsize_.y = viewport->d3d_viewport.Height;
    }

    else if (parent_)
    {
        Viewport* viewport = Renderer::Get()->FindViewport(World::Get()->GetWindow());
        anchor_.x *= parentRectsize_.x / viewport->d3d_viewport.Width;
        anchor_.y *= parentRectsize_.y / viewport->d3d_viewport.Height;
    }

    RefreshAnchorPos();
}

void UIBase::RefreshAnchorPos()
{
    if (!parent_)
    {
        switch (anchorType_)
        {
        case AnchorType::LeftTop:
            anchor_ = Math::Vector2(0.0f, 0.0f);
            break;

        case AnchorType::CenterTop:
            anchor_ = Math::Vector2(parentRectsize_.x / 2, 0.0f);
            break;

        case AnchorType::RightTop:
            anchor_ = Math::Vector2(parentRectsize_.x, 0.0f);
            break;

        case AnchorType::CenterLeft:
            anchor_ = Math::Vector2(0.0f, parentRectsize_.y / 2);
            break;

        case AnchorType::Center:
            anchor_ = Math::Vector2(parentRectsize_.x / 2, parentRectsize_.y / 2);
            break;

        case AnchorType::CenterRight:
            anchor_ = Math::Vector2(parentRectsize_.x, parentRectsize_.y / 2);
            break;

        case AnchorType::LeftBottom:
            anchor_ = Math::Vector2(0.0f, parentRectsize_.y);
            break;

        case AnchorType::CenterBottom:
            anchor_ = Math::Vector2(parentRectsize_.x / 2, parentRectsize_.y);
            break;

        case AnchorType::RightBottom:
            anchor_ = Math::Vector2(parentRectsize_.x, parentRectsize_.y);
            break;
        }
    }

    else if (parent_)
    {
        switch (anchorType_)
        {
        case AnchorType::LeftTop:
            anchor_ = Math::Vector2(-parentRectsize_.x / 2, -parentRectsize_.y / 2);
            break;

        case AnchorType::CenterTop:
            anchor_ = Math::Vector2(0.0f, -parentRectsize_.y / 2);
            break;

        case AnchorType::RightTop:
            anchor_ = Math::Vector2(parentRectsize_.x - parentRectsize_.x / 2, -parentRectsize_.y / 2);
            break;

        case AnchorType::CenterLeft:
            anchor_ = Math::Vector2(-parentRectsize_.x / 2, parentRectsize_.y / 2);
            break;

        case AnchorType::Center:
            anchor_ = Math::Vector2(parentRectsize_.x / 2, parentRectsize_.y / 2);
            break;

        case AnchorType::CenterRight:
            anchor_ = Math::Vector2(parentRectsize_.x, parentRectsize_.y / 2);
            break;

        case AnchorType::LeftBottom:
            anchor_ = Math::Vector2(-parentRectsize_.x / 2, parentRectsize_.y - parentRectsize_.y / 2);
            break;

        case AnchorType::CenterBottom:
            anchor_ = Math::Vector2(parentRectsize_.x / 2, parentRectsize_.y - parentRectsize_.y / 2);
            break;

        case AnchorType::RightBottom:
            anchor_ = Math::Vector2(parentRectsize_.x - parentRectsize_.x / 2, parentRectsize_.y - parentRectsize_.y / 2);
            break;

        }
    }
}
