#pragma once
#include "UI/UIBase.h"


class BitmapComponent : public UIBase
{
public:
	BitmapComponent();


protected:
	virtual void Tick();
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow());

private:
	void LoadBitmap(const std::wstring& kFileName, WindowsWindow* kWindow = World::Get()->GetWindow());
	inline void SetOpacity(const float& cValue) { opacity_ = cValue; }
	Microsoft::WRL::ComPtr<ID2D1Bitmap> bitmap_;

	float opacity_;

	friend class Button;
	friend class Image;
};

