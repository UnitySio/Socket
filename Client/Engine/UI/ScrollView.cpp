#include "ScrollView.h"
#include "BoxComponent.h"
#include "Level/World.h"
#include "Windows/WindowsWindow.h"
#include "Canvas.h"

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
	inner_->SetSize({ 25,50 });

	outer_->SetParent(this);
	inner_->SetParent(this);

	isDown_ = false;
	onMouse_ = false;
	
}

void ScrollView::Render(WindowsWindow* kWindow)
{
	Super::Render(kWindow);
	outer_->Render(kWindow);
	inner_->Render(kWindow);
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
				POINT deltaPos = POINT(pos.x - prevPos_.x , pos.y - prevPos_.y);
				inner_->position_.x += deltaPos.x;
				inner_->position_.y += deltaPos.y;
			}
			prevPos_ = pos;
			return;
		}
	}

	onMouse_ = false;
}
