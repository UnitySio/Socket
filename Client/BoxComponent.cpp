#include "BoxComponent.h"
#include "Engine/Windows/DX/Renderer.h"

BoxComponent::BoxComponent()
{
}

void BoxComponent::Render(WindowsWindow* kWindow)
{
    D2DViewport* d2d_viewport = Renderer::Get()->FindD2DViewport(kWindow);
    if (!d2d_viewport) return;

    D2D1_MATRIX_3X2_F transform;
    d2d_viewport->d2d_render_target->GetTransform(&transform);

    const float half_width = rectsize_.x * 0.5f;
    const float half_height = rectsize_.y * 0.5f;

    const D2D1_RECT_F rect = D2D1::RectF(position_.x - half_width, position_.y - half_height,
        position_.x + half_width, position_.y + half_height);

    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush;
    HRESULT hr = d2d_viewport->d2d_render_target->CreateSolidColorBrush(
        D2D1::ColorF(color_.r / 255.f, color_.g / 255.f, color_.b / 255.f, color_.a / 255.f),
        brush.GetAddressOf());
    if (FAILED(hr)) return;

    D2D1_POINT_2F center = D2D1::Point2F(position_.x, position_.y);
    d2d_viewport->d2d_render_target->SetTransform(D2D1::Matrix3x2F::Rotation(rotation_, center));

    d2d_viewport->d2d_render_target->DrawRectangle(rect, brush.Get(), stroke_);
    d2d_viewport->d2d_render_target->SetTransform(transform);
}
