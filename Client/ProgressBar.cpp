#include "ProgressBar.h"
#include "BoxComponent.h"
#include <Windows.h>
#include "Windows/WindowsWindow.h"

ProgressBar::ProgressBar()
{
	rectsize_ = Math::Vector2(25, 25);

	outer_ = std::make_shared<BoxComponent>();
	inner_ = std::make_shared<BoxComponent>();
	
	inner_->SetFill(true);
	inner_->SetValue(0.0f);

	outer_->SetParent(this);
	inner_->SetParent(this);
}

void ProgressBar::SetValue(const float& value)
{
	inner_->SetValue(value);
}

void ProgressBar::SetTouchEnable(const bool& flag)
{
	touchable_ = flag;
}

void ProgressBar::SetBoxSize(const Math::Vector2 size)
{
	outer_->SetSize(size);
	inner_->SetSize(size);
	rectsize_ = outer_->rectsize_ / 2;
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

	if (pos.x >= position_.x - rectsize_.x && pos.x <= position_.x + rectsize_.x)
	{
		if (pos.y >= position_.y - rectsize_.y && pos.y <= position_.y + rectsize_.y)
		{
			auto temp = pos.x - (position_.x - rectsize_.x);
			temp = temp / (rectsize_.x * 2);

			inner_->SetValue(temp);
			return;
		}
	}
}
