#pragma once
#include "UIBase.h"

class StringComponent : public UIBase
{
public:
	StringComponent();
	StringComponent(const UIBase& parent);

	void SetText(const std::wstring& kString);
	
protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;

private:
	void SetFontStyle(const bool& bold, const bool& style);
	void SetAlignment(DWRITE_TEXT_ALIGNMENT text, DWRITE_PARAGRAPH_ALIGNMENT para);
	DWRITE_TEXT_ALIGNMENT textAlignment_;
	DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment_;

	float font_size;
	std::wstring string_;
	Microsoft::WRL::ComPtr<IDWriteFactory5> dwrite_factory_;
	Microsoft::WRL::ComPtr<IDWriteFontCollection1> dwrite_font_collection_;
	DWRITE_FONT_WEIGHT bold_;
	DWRITE_FONT_STYLE style_;
	friend class Button;
	friend class TextBlock;

};

