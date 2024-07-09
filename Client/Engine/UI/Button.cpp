#include "Button.h"
#include "BoxComponent.h"
#include "StringComponent.h"
#include "Canvas.h"
#include <Windows.h>
#include "Windows/WindowsWindow.h"
#include "Misc/Function.h"

Button::Button()
{
	rectsize_ = Math::Vector2(25, 25);
	box_ = std::make_shared<BoxComponent>();
	string_ = std::make_shared<StringComponent>();

	box_->SetParent(this);
	string_->SetParent(this);

	string_->SetOffset(Math::Vector2(15, 25));
	isDown_ = false;
}

void Button::SetText(const std::wstring& kString)
{
	string_->SetText(kString);
}

void Button::SetBoxSize(const Math::Vector2& kSize)
{
	box_->SetSize(kSize);
	rectsize_ = box_->rectsize_ / 2;
}

void Button::SetFill(const bool& kFlag)
{
	box_->SetFill(kFlag);
}

void Button::SetBoxColor(const Math::Color& kColor)
{
	box_->SetColor(kColor);
}

void Button::SetTextColor(const Math::Color& kColor)
{
	string_->SetColor(kColor);
}

void Button::SetEnable(const bool& kFlag)
{
	Super::SetEnable(kFlag);
	box_->SetEnable(kFlag);
	string_->SetEnable(kFlag);
}

const bool& Button::OnMouse()
{
	return onMouse_;
}

void Button::Render(WindowsWindow* kWindow)
{
	Super::Render(kWindow);
	box_->Render(kWindow);
	string_->Render(kWindow);
}

void Button::Tick()
{
	Super::Tick();
	POINT pos{};
	GetCursorPos(&pos);
	ScreenToClient(World::Get()->GetWindow()->GetHWnd(), &pos);
	

	

	if (pos.x >= position_.x - rectsize_.x && pos.x <= position_.x + rectsize_.x)
	{
		if (pos.y >= position_.y - rectsize_.y && pos.y <= position_.y + rectsize_.y)
		{
			/*wchar_t str[100];
			swprintf(str, L"%d, %d", pos.x, pos.y);
			string_->SetText(str);*/
			/*if (onClickedFunc_ && isDown_)
				(*onClickedFunc_)();*/
			onMouse_ = true;
			return;
		}
	}
	onMouse_ = false;

	
}