#include "UIBase.h"
#include <d3d11.h>
#include <wrl.h>
#include <d2d1.h>
#include "Engine/Windows/DX/Renderer.h"


UIBase::UIBase()
    :
    position_(Math::Vector2(0,0)),
    rectsize_(Math::Vector2(0,0)),
    color_(Math::Color(255,255,255,255)),
    rotation_(0),
    parent_(nullptr)
{
}

void UIBase::SetParent(UIBase* parent)
{
	parent_->children_.push_back(this);
	parent_ = parent;
}

void UIBase::SetSize(const Math::Vector2& value)
{
    rectsize_ = value;
}


