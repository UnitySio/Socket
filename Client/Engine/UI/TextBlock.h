#pragma once
#include "UIBase.h"
#include <memory>

class StringComponent;

class TextBlock : public UIBase
{
public:
	enum class TextAlignment
	{
		Center = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER,
		Justified = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_JUSTIFIED,
		Leading = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING,
		Trailing = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_TRAILING
	};
	enum class ParaAlignment
	{
		Center = DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER,
		Far = DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_FAR,
		Near = DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_NEAR
	};

	TextBlock();
	void SetText(const std::wstring& kString);
	void SetSize(const Math::Vector2& kSize);
	void SetTextColor(const Math::Color& kColor);
	void SetAlignment(const TextAlignment& text = TextAlignment::Center, const ParaAlignment& para = ParaAlignment::Center);
	/// <summary>
	/// Both default is false
	/// </summary>
	/// <param name="First : Bold"></param>
	/// <param name="Second : Italic"></param>
	void SetFontStyle(const bool& bold = false, const bool& italic = false);

protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;
	virtual void Tick() override;

private:
	std::shared_ptr<StringComponent> str_;
};

