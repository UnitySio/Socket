#pragma once
#include "UI/UIBase.h"


class BitmapComponent : public UIBase
{
public:
	BitmapComponent();
	virtual ~BitmapComponent();

	void LoadBitmap(const std::wstring& kFileName, WindowsWindow* kWindow = World::Get()->GetWindow());

protected:
	virtual void Tick();
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow());

private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap> bitmap_;
	Microsoft::WRL::ComPtr<IWICImagingFactory> wic_imaging_factory_;
	friend class Button;
};

