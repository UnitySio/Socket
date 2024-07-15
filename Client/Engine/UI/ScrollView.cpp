#include "pch.h"
#include "ScrollView.h"
#include "BoxComponent.h"
#include "Level/World.h"
#include "Windows/WindowsWindow.h"
#include "Canvas.h"
#include "ProgressBar.h"

ScrollView::ScrollView()
{
	rectsize_ = Math::Vector2(25, 25);

	outer_ = std::make_shared<BoxComponent>();
	inner_ = std::make_shared<BoxComponent>();

	inner_->SetFill(true);
	inner_->SetValue(0.0f);
	inner_->SetInnerScroll(true);
	inner_->outer_ = outer_;
	inner_->SetFill(true);
	inner_->SetValue(1.0f);
	inner_->SetSize({ outer_->rectsize_.x,outer_->rectsize_.y });

	outer_->SetParent(this);
	inner_->SetParent(this);

	isDown_ = false;
	onMouse_ = false;
	isVertical_ = true;
	
}

void ScrollView::SetSize(const Math::Vector2& kSize)
{
	Super::SetSize(kSize);
}

void ScrollView::SetEnableSideBar(const bool& kFlag)
{
	if (kFlag)
	{
		sidebar_ = std::make_shared<ScrollView>();
		sidebar_->SetParent(this);
		sidebar_->SetPosition({ 100,0 });
		sidebar_->SetSize({ 50,50 });
	}
	
}

void ScrollView::Render(WindowsWindow* kWindow)
{
	Super::Render(kWindow);
	outer_->Render(kWindow);
	inner_->Render(kWindow);
	if (sidebar_)
		sidebar_->Render(kWindow);
}

void ScrollView::Tick()
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
			
			if (isDown_)
			{
				if (isVertical_)
				{
					POINT deltaPos = POINT(pos.x - prevPos_.x, pos.y - prevPos_.y);
					inner_->position_.y += deltaPos.y;
				}

				else if (!isVertical_)
				{
					POINT deltaPos = POINT(pos.x - prevPos_.x, pos.y - prevPos_.y);
					inner_->position_.x += deltaPos.x;
				}
			}
			prevPos_ = pos;
			return;
		}
	}

	onMouse_ = false;
}
