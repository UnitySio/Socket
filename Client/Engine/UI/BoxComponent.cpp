#include "BoxComponent.h"
#include "../Engine/Windows/DX/Renderer.h"

BoxComponent::BoxComponent()
{
    rectsize_ = Math::Vector2(50, 50);
    isFilled_ = false;
    value_ = 1.0f;
    isInnerScroll_ = false;
}

void BoxComponent::SetColor(const Math::Color& color)
{
    color_ = color;
}

void BoxComponent::SetFill(const bool& flag)
{
    isFilled_ = flag;
}

void BoxComponent::SetValue(const float value)
{
    if (value > 1.0f)
        value_ = 1.0f;
    else if (value < 0.0f)
        value_ = 0.0f;
    else
        value_ = value * 2.0f - 1.0f;
}

void BoxComponent::SetVertical(const bool& flag)
{
    isVertical_ = flag;
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
    D2D1_RECT_F rect;
    if (!isVertical_)
    {
        rect = D2D1::RectF(GetPosition().x - half_width, GetPosition().y - half_height,
            GetPosition().x + half_width * value_, GetPosition().y + half_height);
    }

    else if (isVertical_)
    {
        rect = D2D1::RectF(GetPosition().x - half_width, GetPosition().y - half_height * value_,
            GetPosition().x + half_width, GetPosition().y + half_height);
    }
    

    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush;
    HRESULT hr = d2d_viewport->d2d_render_target->CreateSolidColorBrush(
        D2D1::ColorF(color_.r / 255.f, color_.g / 255.f, color_.b / 255.f, color_.a / 255.f),
        brush.GetAddressOf());
    if (FAILED(hr)) return;

    D2D1_POINT_2F center = D2D1::Point2F(GetPosition().x, GetPosition().y);
    d2d_viewport->d2d_render_target->SetTransform(D2D1::Matrix3x2F::Rotation(rotation_, center));


    Microsoft::WRL::ComPtr<ID2D1Layer> layer;
    d2d_viewport->d2d_render_target->CreateLayer(nullptr, &layer);

    if (isInnerScroll_)
    {
        D2D1_RECT_F clipRect = D2D1::RectF(outer_->GetPosition().x - outer_->rectsize_.x/2, outer_->GetPosition().y - outer_->rectsize_.y / 2,
            outer_->GetPosition().x + outer_->rectsize_.x / 2 * value_, outer_->GetPosition().y + outer_->rectsize_.y / 2);
        d2d_viewport->d2d_render_target->PushLayer(
            D2D1::LayerParameters(
                clipRect,
                nullptr,
                D2D1_ANTIALIAS_MODE_PER_PRIMITIVE,
                D2D1::IdentityMatrix(),
                1.0f,
                nullptr,
                D2D1_LAYER_OPTIONS_NONE),
            layer.Get()
        );


        if (!isFilled_)
            d2d_viewport->d2d_render_target->DrawRectangle(rect, brush.Get(), stroke_);
        else if (isFilled_)
            d2d_viewport->d2d_render_target->FillRectangle(rect, brush.Get());

        d2d_viewport->d2d_render_target->PopLayer();

        d2d_viewport->d2d_render_target->SetTransform(transform);
    }

    else if (!isInnerScroll_)
    {

        if (!isFilled_)
            d2d_viewport->d2d_render_target->DrawRectangle(rect, brush.Get(), stroke_);
        else if (isFilled_)
            d2d_viewport->d2d_render_target->FillRectangle(rect, brush.Get());


        d2d_viewport->d2d_render_target->SetTransform(transform);
    }
    
}