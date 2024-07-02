#include "UIBase.h"
#include <d3d11.h>
#include <wrl.h>
#include <d2d1.h>
#include "Engine/Windows/DX/Renderer.h"


UIBase::UIBase()
    :
    position_(Math::Vector2(0, 0)),
    rectsize_(Math::Vector2(100.0f, 100.0f)),
    color_(Math::Color(255, 255, 255, 255)),
    rotation_(0),
    parent_(nullptr),
    stroke_(1.0f)
{
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

const Math::Vector2& UIBase::GetPosition()
{
    if (parent_)
        return position_ + parent_->GetPosition();
    return position_;
}


