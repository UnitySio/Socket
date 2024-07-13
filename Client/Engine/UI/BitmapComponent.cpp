#include "BitmapComponent.h"
#include "Windows/DX/Renderer.h"
#include <d2d1.h>
#include <wincodec.h>


BitmapComponent::BitmapComponent()
    :Super(),
    bitmap_(nullptr)
{
    position_ = Math::Vector2::Zero();
    rectsize_ = Math::Vector2::Zero();
    rotation_ = 0.0f;
    opacity_ = 1.0f;

}



void BitmapComponent::LoadBitmap(const std::wstring& kFileName, WindowsWindow* kWindow)
{
    D2DViewport* d2d_viewport = Renderer::Get()->FindD2DViewport(kWindow);
    
    Microsoft::WRL::ComPtr<IWICImagingFactory> wic_imaging_factory_ = Renderer::Get()->GetImageFactory();
    
    Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
    HRESULT hr = wic_imaging_factory_->CreateDecoderFromFilename(kFileName.c_str(), nullptr, GENERIC_READ,
        WICDecodeMetadataCacheOnLoad, decoder.GetAddressOf());

    Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
    hr = decoder->GetFrame(0, frame.GetAddressOf());

    Microsoft::WRL::ComPtr<IWICFormatConverter> format_converter;
    hr = wic_imaging_factory_->CreateFormatConverter(format_converter.GetAddressOf());

    hr = format_converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone,
        nullptr, 0.f, WICBitmapPaletteTypeMedianCut);

    hr = d2d_viewport->d2d_render_target->CreateBitmapFromWicBitmap(format_converter.Get(), bitmap_.GetAddressOf());
}

void BitmapComponent::Tick()
{
	Super::Tick();

}

void BitmapComponent::Render(WindowsWindow* kWindow)
{
	Super::Render(kWindow);
    D2DViewport* d2d_viewport = Renderer::Get()->FindD2DViewport(kWindow);
    if (!d2d_viewport) return;

    D2D1_MATRIX_3X2_F transform;
    d2d_viewport->d2d_render_target->GetTransform(&transform);

    const float half_width = rectsize_.x * 0.5f;
    const float half_height = rectsize_.y * 0.5f;
    
    const D2D1_RECT_F rect = D2D1::RectF(GetPosition().x - half_width, GetPosition().y - half_height,
        GetPosition().x + half_width, GetPosition().y + half_height);

    

    D2D1_POINT_2F center = D2D1::Point2F(GetPosition().x, GetPosition().y);
    d2d_viewport->d2d_render_target->SetTransform(D2D1::Matrix3x2F::Rotation(rotation_, center));

    d2d_viewport->d2d_render_target->DrawBitmap(bitmap_.Get(), rect, opacity_);
    d2d_viewport->d2d_render_target->SetTransform(transform);
}

