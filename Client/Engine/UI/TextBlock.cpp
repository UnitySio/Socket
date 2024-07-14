#include "pch.h"
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

void TextBlock::SetTextColor(const Math::Color& kColor)
{
	str_->SetColor(kColor);
}

void TextBlock::SetAlignment(const TextAlignment& text, const ParaAlignment& para)
{
	str_->SetAlignment(static_cast<DWRITE_TEXT_ALIGNMENT>(text), static_cast<DWRITE_PARAGRAPH_ALIGNMENT>(para));
}



void TextBlock::SetFontStyle(const bool& bold, const bool& italic)
{
	str_->SetFontStyle(bold, italic);
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
