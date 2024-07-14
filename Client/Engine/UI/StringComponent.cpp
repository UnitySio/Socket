#include "pch.h"
#include "StringComponent.h"
#include "Windows/DX/Renderer.h"

StringComponent::StringComponent()
    :font_size(24.0f),
    textAlignment_(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER),
    paragraphAlignment_(DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER),
    bold_(DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_MEDIUM),
    style_(DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL)
{
    rectsize_ = Math::Vector2(100,100);

    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory5),
        reinterpret_cast<IUnknown**>(dwrite_factory_.GetAddressOf()));

    Microsoft::WRL::ComPtr<IDWriteFontSetBuilder1> font_set_builder;
    hr = dwrite_factory_->CreateFontSetBuilder(font_set_builder.GetAddressOf());

    Microsoft::WRL::ComPtr<IDWriteFontFile> silver_font;
    hr = dwrite_factory_->CreateFontFileReference(L".\\Game_Data\\Silver.ttf", nullptr, silver_font.GetAddressOf());

    hr = font_set_builder->AddFontFile(silver_font.Get());

    Microsoft::WRL::ComPtr<IDWriteFontFile> nanum_font;
    hr = dwrite_factory_->CreateFontFileReference(L".\\Game_Data\\NanumBarunGothic.ttf", nullptr,
        nanum_font.GetAddressOf());

    hr = font_set_builder->AddFontFile(nanum_font.Get());

    Microsoft::WRL::ComPtr<IDWriteFontSet> font_set;
    hr = font_set_builder->CreateFontSet(font_set.GetAddressOf());

    hr = dwrite_factory_->CreateFontCollectionFromFontSet(font_set.Get(), dwrite_font_collection_.GetAddressOf());
}

StringComponent::StringComponent(const UIBase& parent)
    :font_size(24.0f)
{
    position_ = parent.position_;
    rectsize_ = parent.rectsize_;
    color_ = parent.color_;
    stroke_ = parent.stroke_;
    rotation_ = parent.rotation_;
    parent_ = parent.parent_;
    children_ = parent.children_;
}

void StringComponent::SetText(const std::wstring& kString)
{
    string_ = kString;
}

void StringComponent::Render(WindowsWindow* kWindow)
{
    Super::Render(kWindow);
    D2DViewport* d2d_viewport = Renderer::Get()->FindD2DViewport(kWindow);
    if (!d2d_viewport) return;

    D2D1_MATRIX_3X2_F transform;
    d2d_viewport->d2d_render_target->GetTransform(&transform);

    const float half_width = rectsize_.x / 2;
    const float half_height = rectsize_.y / 2;

    //const D2D1_RECT_F rect = D2D1::RectF(position_.x - rectsize_.x, position_.y + rectsize_.y, position_.x, position_.y);
    const D2D1_RECT_F rect = D2D1::RectF(GetPosition().x - half_width, GetPosition().y + half_height,
        GetPosition().x + half_width, GetPosition().y + 2 * half_height);

    Microsoft::WRL::ComPtr<IDWriteTextFormat> text_format;
    HRESULT hr = dwrite_factory_->CreateTextFormat(L"Silver", dwrite_font_collection_.Get(),
        bold_, style_,
        DWRITE_FONT_STRETCH_NORMAL, font_size, L"en-us",
        text_format.GetAddressOf());
    if (FAILED(hr)) return;

    text_format->SetTextAlignment(textAlignment_);
    text_format->SetParagraphAlignment(paragraphAlignment_);

    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> brush;
    hr = d2d_viewport->d2d_render_target->CreateSolidColorBrush(
        D2D1::ColorF(color_.r / 255.f, color_.g / 255.f, color_.b / 255.f, color_.a / 255.f),
        brush.GetAddressOf());
    if (FAILED(hr)) return;

    d2d_viewport->d2d_render_target->DrawTextW(string_.c_str(), static_cast<UINT32>(string_.size()),
        text_format.Get(), rect, brush.Get());
    d2d_viewport->d2d_render_target->SetTransform(transform);
}

void StringComponent::SetFontStyle(const bool& bold, const bool& style)
{
    if(bold)
        bold_ = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_BOLD;
    else if(!bold)
        bold_ = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_MEDIUM;

    if (style)
        style_ = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_ITALIC;
    else if (!style)
        style_ = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL;
}

void StringComponent::SetAlignment(DWRITE_TEXT_ALIGNMENT text, DWRITE_PARAGRAPH_ALIGNMENT para)
{
    textAlignment_ = text;
    paragraphAlignment_ = para;
}
