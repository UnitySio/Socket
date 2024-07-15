#include "pch.h"
#include "ProgressBar.h"
#include "BoxComponent.h"
#include <Windows.h>
#include "Windows/WindowsWindow.h"
#include "Canvas.h"

ProgressBar::ProgressBar()
{
	rectsize_ = Math::Vector2(25, 25);

	outer_ = std::make_shared<BoxComponent>();
	inner_ = std::make_shared<BoxComponent>();
	
	inner_->SetFill(true);
	inner_->SetValue(0.0f);

	outer_->SetParent(this);
	inner_->SetParent(this);

	isDown_ = false;
	onMouse_ = false;
	touchable_ = false;
	isVertical_ = false;
}

void ProgressBar::SetValue(const float& value)
{
	inner_->SetValue(value);
}


void ProgressBar::SetBoxSize(const Math::Vector2 size)
{
	outer_->SetSize(size);
	inner_->SetSize(size);
	rectsize_ = outer_->rectsize_ / 2;
}

const bool& ProgressBar::OnMouse()
{
	return onMouse_;
}

void ProgressBar::SetTouchEnable(const bool& flag)
{
	touchable_ = flag;
}

void ProgressBar::SetVertical(const bool& flag)
{
	isVertical_ = flag;
	inner_->SetVertical(flag);
}

void ProgressBar::SetOutlineColor(const Math::Color& kColor)
{
	outer_->SetColor(kColor);
}

void ProgressBar::SetInnerBarColor(const Math::Color& kColor)
{
	inner_->SetColor(kColor);
}

void ProgressBar::Render(WindowsWindow* kWindow)
{
	Super::Render(kWindow);
	outer_->Render(kWindow);
	inner_->Render(kWindow);
}

void ProgressBar::Tick()
{
	Super::Tick();
	POINT pos{};
	GetCursorPos(&pos);
	ScreenToClient(World::Get()->GetWindow()->GetHWnd(), &pos);
	
	isDown_ = Canvas::Get()->IsDown();

	if (pos.x >= position_.x - rectsize_.x && pos.x <= position_.x + rectsize_.x)
	{
		if (pos.y >= position_.y - rectsize_.y && pos.y <= position_.y + rectsize_.y)
		{
			onMouse_ = true;
			if (!isVertical_)
			{
				auto temp = pos.x - (position_.x - rectsize_.x);
				temp = temp / (rectsize_.x * 2);
				value_ = temp;
			}

			else if (isVertical_)
			{
				auto temp = (position_.y + rectsize_.y) - pos.y ;
				temp = temp / (rectsize_.y * 2);
				value_ = temp;
			}
			

			if (touchable_)
			{
				if (isDown_ && onMouse_)
				{
					inner_->SetValue(value_);
				}
			}

			return;
		}
	}

	onMouse_ = false;
}