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
	float font_size;
	std::wstring string_;
	Microsoft::WRL::ComPtr<IDWriteFactory5> dwrite_factory_;
	Microsoft::WRL::ComPtr<IDWriteFontCollection1> dwrite_font_collection_;
};

