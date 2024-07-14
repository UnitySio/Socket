#include "pch.h"
#include "LineComponent.h"
#include "Windows/DX/Renderer.h"

LineComponent::LineComponent()
    :Super(),
    start_(Math::Vector2::Zero()),
    end_(Math::Vector2::Zero()),
    color_(Math::Color::White),
    stroke_(1.0f)
{
}

void LineComponent::Tick()
{
	Super::Tick();
}

void LineComponent::Render(WindowsWindow* kWindow)
{
	Super::Render(kWindow);

    D2DViewport* d2d_viewport = Renderer::Get()->FindD2DViewport(kWindow);
    if (!d2d_viewport) return;

    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush;
    HRESULT hr = d2d_viewport->d2d_render_target->CreateSolidColorBrush(
        D2D1::ColorF(color_.r / 255.f, color_.g / 255.f, color_.b / 255.f, color_.a / 255.f),
        brush.GetAddressOf());
    if (FAILED(hr)) return;

    d2d_viewport->d2d_render_target->DrawLine(D2D1::Point2F(start_.x, start_.y), D2D1::Point2F(end_.x, end_.y), brush.Get(),
        stroke_);
}
