#include "Button.h"
#include "BoxComponent.h"
#include "StringComponent.h"

Button::Button()
{
	box_ = std::make_shared<BoxComponent>();
	string_ = std::make_shared<StringComponent>();
	box_->SetParent(this);
	string_->SetParent(this);
}

void Button::SetText(const std::wstring& kString)
{
	string_->SetText(kString);
}

void Button::SetBoxSize(const Math::Vector2& size)
{
	box_->SetSize(size);
}

void Button::Render(WindowsWindow* kWindow)
{
	box_->Render(kWindow);
	string_->Render(kWindow);
}
