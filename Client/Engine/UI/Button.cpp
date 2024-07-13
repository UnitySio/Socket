#include "Button.h"
#include "BoxComponent.h"
#include "StringComponent.h"
#include "Canvas.h"
#include <Windows.h>
#include "Windows/WindowsWindow.h"
#include "Misc/Function.h"
#include "BitmapComponent.h"
#include "TextBlock.h"
#include "Image.h"

Button::Button()
{
	rectsize_ = Math::Vector2(25, 25);
	box_ = std::make_shared<BoxComponent>();
	string_ = std::make_shared<TextBlock>();

	box_->SetParent(this);
	string_->SetParent(this);

	//string_->SetOffset(Math::Vector2(15, 25));
	isDown_ = false;
	isImage_ = false;
	onMouse_ = false;
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
	image_->SetEnable(kFlag);
}

const bool& Button::OnMouse()
{
	return onMouse_;
}

void Button::SetImage(const std::wstring& kFileName)
{
	isImage_ = true;
	image_ = std::make_shared<Image>();
	image_->SetImage(kFileName);
	image_->SetParent(this);
	image_->SetSize(rectsize_);
}

void Button::RemoveImage()
{
	isImage_ = false;
}

void Button::Render(WindowsWindow* kWindow)
{
	Super::Render(kWindow);
	if (!isImage_)
		box_->Render(kWindow);

	else if (isImage_)
		image_->Render(kWindow);

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
			onMouse_ = true;
			return;
		}
	}
	onMouse_ = false;

	
}