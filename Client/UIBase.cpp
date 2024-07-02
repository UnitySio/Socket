#include "UIBase.h"
#include <d3d11.h>
#include <wrl.h>
#include <d2d1.h>
#include "Engine/Windows/DX/Renderer.h"


UIBase::UIBase()
    :
    position_(Math::Vector2(0, 0)),
    color_(Math::Color(255, 255, 255, 255)),
    rotation_(0),
    parentRectsize_(640, 480),
    rectsize_(640, 480),
    parent_(nullptr),
    stroke_(1.0f)
{
    //Viewport* viewport = Renderer::Get()->FindViewport(World::Get()->GetWindow());
    //rectsize_ = Math::Vector2(viewport->d3d_viewport.Width, viewport->d3d_viewport.Height);
}

void UIBase::SetParent(UIBase* parent)
{
	parent->children_.push_back(this);
	parent_ = parent;
    rectsize_ = parent->rectsize_;
}

void UIBase::SetSize(const Math::Vector2& value)
{
    rectsize_ = value;
}

void UIBase::SetPosition(const Math::Vector2& pos)
{
    position_ = pos;
}

const Math::Vector2 UIBase::GetPosition()
{
    if (parent_)
        return position_ + parent_->GetPosition();
    return position_;
}

void UIBase::SetAnchorType(const AnchorType& type)
{
    anchorType_ = type;

    switch (type)
    {
    case AnchorType::LeftTop:
        anchor_ = Math::Vector2(0.0f, 0.0f);
        break;

    case AnchorType::CenterTop:
        anchor_ = Math::Vector2(parent_->rectsize_.x / 2, 0.0f);
        break;

    case AnchorType::RightTop:
        anchor_ = Math::Vector2(parent_->rectsize_.x, 0.0f);
        break;

    }
}

void UIBase::Render(WindowsWindow* kWindow)
{
    
}
