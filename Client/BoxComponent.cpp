#include "BoxComponent.h"
#include "Engine/Windows/DX/Renderer.h"

BoxComponent::BoxComponent()
{
    rectsize_ = Math::Vector2(50, 50);
    isFilled_ = false;
    value_ = 1.0f;
}

void BoxComponent::SetFill(const bool& flag)
{
    isFilled_ = flag;
}

void BoxComponent::SetValue(const float& value)
{
    if (value > 1.0f)
        value_ = 1.0f;
    else if (value < 0.0f)
        value_ = 0.0f;
    else
        value_ = value * 2.0f - 1.0f;
}

void BoxComponent::Render(WindowsWindow* kWindow)
{
    Super::Render(kWindow);
    D2DViewport* d2d_viewport = Renderer::Get()->FindD2DViewport(kWindow);
    if (!d2d_viewport) return;

    D2D1_MATRIX_3X2_F transform;
    d2d_viewport->d2d_render_target->GetTransform(&transform);

    const float half_width = rectsize_.x * 0.5f;
    const float half_height = rectsize_.y * 0.5f;

    const D2D1_RECT_F rect = D2D1::RectF(GetPosition().x - half_width, GetPosition().y - half_height,
        GetPosition().x + half_width * value_, GetPosition().y + half_height);

    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush;
    HRESULT hr = d2d_viewport->d2d_render_target->CreateSolidColorBrush(
        D2D1::ColorF(color_.r / 255.f, color_.g / 255.f, color_.b / 255.f, color_.a / 255.f),
        brush.GetAddressOf());
    if (FAILED(hr)) return;

    D2D1_POINT_2F center = D2D1::Point2F(GetPosition().x, GetPosition().y);
    d2d_viewport->d2d_render_target->SetTransform(D2D1::Matrix3x2F::Rotation(rotation_, center));

    if (!isFilled_)
        d2d_viewport->d2d_render_target->DrawRectangle(rect, brush.Get(), stroke_);
    else if (isFilled_)
        d2d_viewport->d2d_render_target->FillRectangle(rect, brush.Get());
    d2d_viewport->d2d_render_target->SetTransform(transform);
}