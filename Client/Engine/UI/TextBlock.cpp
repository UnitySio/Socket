#include "TextBlock.h"
#include "StringComponent.h"

TextBlock::TextBlock()
{
	str_ = std::make_shared<StringComponent>();

	str_->SetParent(this);
}

void TextBlock::SetText(const std::wstring& kString)
{
	str_->SetText(kString);
}

void TextBlock::SetSize(const Math::Vector2& kSize)
{
	str_->SetSize(kSize);
}

void TextBlock::Render(WindowsWindow* kWindow)
{
	Super::Render(kWindow);
	str_->Render(kWindow);
}

void TextBlock::Tick()
{
	Super::Tick();

}
