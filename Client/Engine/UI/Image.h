#pragma once
#include "UIBase.h"

class BitmapComponent;

class Image : public UIBase
{
public:
	Image();
	void SetOpacity(const float& cValue);
	void SetImage(const std::wstring& kFileName, WindowsWindow* kWindow = World::Get()->GetWindow());

protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;
	virtual void Tick() override;

private:
	std::shared_ptr<BitmapComponent> image_;
	friend class Button;
};

