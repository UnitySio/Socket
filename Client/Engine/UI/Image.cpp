#include "pch.h"
#include "Image.h"
#include "BitmapComponent.h"

Image::Image()
{
	image_ = std::make_shared<BitmapComponent>();
	image_->SetParent(this);
}

void Image::SetOpacity(const float& cValue)
{
	image_->SetOpacity(cValue);
}

void Image::SetImage(const std::wstring& kFileName, WindowsWindow* kWindow)
{
	image_->LoadBitmapW(kFileName, kWindow);
}

void Image::Render(WindowsWindow* kWindow)
{
	Super::Render(kWindow);
	image_->Render(kWindow);
}

void Image::Tick()
{
	Super::Tick();
	image_->Tick();
}
