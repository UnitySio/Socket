#pragma once
#include "UI/UIBase.h"


class BitmapComponent : public UIBase
{
public:
	BitmapComponent();

	void LoadBitmap(const std::wstring& kFileName, WindowsWindow* kWindow = World::Get()->GetWindow());

protected:
	virtual void Tick();
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow());

private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap> bitmap_;
	Math::Vector2 position_;
	Math::Vector2 size_;
	float rotation_;

	Microsoft::WRL::ComPtr<IWICImagingFactory> wic_imaging_factory_;

};

