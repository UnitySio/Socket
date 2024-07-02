#include "Button.h"
#include "BoxComponent.h"
#include "StringComponent.h"

Button::Button()
{
	rectsize_ = Math::Vector2(50, 50);
	box_ = std::make_shared<BoxComponent>();
	string_ = std::make_shared<StringComponent>();
	box_->SetParent(this);
	string_->SetParent(this);
	string_->SetOffset(Math::Vector2(15, 25));
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
	Super::Render(kWindow);
	box_->Render(kWindow);
	string_->Render(kWindow);
}
