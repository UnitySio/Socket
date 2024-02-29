#define STB_IMAGE_IMPLEMENTATION

#include "Graphics.h"

#include <iostream>

#include "../Core.h"
#include "box2d/b2_math.h"

#include <wincodec.h>

Graphics::Graphics() :
    d3d_device_(nullptr),
    d3d_device_context_(nullptr),
    d3d_render_target_view_(nullptr),
    dxgi_swap_chain_(nullptr),
    d2d_factory_(nullptr),
    d2d_render_target_(nullptr)
{
}

Graphics::~Graphics()
{
    if (d2d_render_target_) d2d_render_target_->Release();
    if (d2d_factory_) d2d_factory_->Release();
    if (d3d_render_target_view_) d3d_render_target_view_->Release();
    if (dxgi_swap_chain_) dxgi_swap_chain_->Release();
    if (d3d_device_context_) d3d_device_context_->Release();
    if (d3d_device_) d3d_device_->Release();
}

bool Graphics::Init()
{
    return InitDeviceD3D() && InitFactoryD2D();
}

bool Graphics::InitDeviceD3D()
{
    DXGI_SWAP_CHAIN_DESC swap_chain_desc;
    ZeroMemory(&swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));

    swap_chain_desc.BufferDesc.Width = Core::Get()->GetResolution().x;
    swap_chain_desc.BufferDesc.Height = Core::Get()->GetResolution().y;
    swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
    swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    swap_chain_desc.SampleDesc.Count = 1;
    swap_chain_desc.SampleDesc.Quality = 0;

    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.BufferCount = 1;
    swap_chain_desc.OutputWindow = Core::Get()->GetWindowHandle();
    swap_chain_desc.Windowed = TRUE;
    swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swap_chain_desc.Flags = 0;

    constexpr D3D_FEATURE_LEVEL feature_levels[] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1
    };

    HRESULT result = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        feature_levels,
        2,
        D3D11_SDK_VERSION,
        &swap_chain_desc,
        &dxgi_swap_chain_,
        &d3d_device_,
        nullptr,
        &d3d_device_context_
    );

    if (FAILED(result)) return false;
    return InitRenderTargetD3D();
}

bool Graphics::InitRenderTargetD3D()
{
    ID3D11Texture2D* back_buffer;

    HRESULT result = dxgi_swap_chain_->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
    if (FAILED(result)) return false;

    result = d3d_device_->CreateRenderTargetView(back_buffer, nullptr, &d3d_render_target_view_);
    back_buffer->Release();

    d3d_viewport_.TopLeftX = 0;
    d3d_viewport_.TopLeftY = 0;
    d3d_viewport_.Width = static_cast<float>(Core::Get()->GetResolution().x);
    d3d_viewport_.Height = static_cast<float>(Core::Get()->GetResolution().y);
    d3d_viewport_.MinDepth = 0.0f;
    d3d_viewport_.MaxDepth = 1.0f;

    return SUCCEEDED(result);
}

bool Graphics::InitFactoryD2D()
{
    HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory_);

    if (FAILED(result)) return false;
    return InitRenderTargetD2D();
}

bool Graphics::InitRenderTargetD2D()
{
    const float dpi = GetDpiForWindow(Core::Get()->GetWindowHandle());
    const D2D1_RENDER_TARGET_PROPERTIES render_target_properties = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
        dpi,
        dpi
    );

    IDXGISurface* back_buffer;

    HRESULT result = dxgi_swap_chain_->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
    if (FAILED(result)) return false;

    result = d2d_factory_->CreateDxgiSurfaceRenderTarget(back_buffer, &render_target_properties, &d2d_render_target_);
    back_buffer->Release();

    return SUCCEEDED(result);
}

void Graphics::BeginRenderD3D()
{
    constexpr float clear_color[] = {0.f, 0.f, 0.f, 1.f};

    d3d_device_context_->OMSetRenderTargets(1, &d3d_render_target_view_, nullptr);
    d3d_device_context_->ClearRenderTargetView(d3d_render_target_view_, clear_color);
    d3d_device_context_->RSSetViewports(1, &d3d_viewport_);
}

void Graphics::EndRenderD3D()
{
    if (dxgi_swap_chain_->Present(1, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED) return;
    dxgi_swap_chain_->Present(1, 0);
}

void Graphics::Resize()
{
    if (!d3d_device_context_) return;
    d3d_device_context_->OMSetRenderTargets(0, nullptr, nullptr);
    d3d_render_target_view_->Release();

    dxgi_swap_chain_->ResizeBuffers(0, 0, 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
}

void Graphics::DrawLine(b2Vec2 start, b2Vec2 end, b2Color color)
{
    ID2D1SolidColorBrush* brush;
    d2d_render_target_->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &brush);

    d2d_render_target_->SetTransform(D2D1::Matrix3x2F::Identity());

    d2d_render_target_->DrawLine(
        D2D1::Point2F(start.x, start.y),
        D2D1::Point2F(end.x, end.y),
        brush
    );

    brush->Release();
}

void Graphics::DrawBox(b2Vec2 center, b2Vec2 size, float angle, b2Color color)
{
    const float half_size_x = size.x / 2.f;
    const float half_size_y = size.y / 2.f;

    const D2D1_RECT_F rectangle = D2D1::RectF(
        center.x - half_size_x,
        center.y - half_size_y,
        center.x + half_size_x,
        center.y + half_size_y
    );

    const D2D_COLOR_F d2d_color = D2D1::ColorF(color.r,
                                               color.g,
                                               color.b,
                                               color.a);

    ID2D1SolidColorBrush* brush;
    d2d_render_target_->CreateSolidColorBrush(d2d_color, &brush);

    // 라디안을 각도로 변환
    angle = angle * 180.f / b2_pi;

    D2D1_POINT_2F point = D2D1::Point2F(center.x, center.y);
    d2d_render_target_->SetTransform(D2D1::Matrix3x2F::Rotation(angle, point));

    d2d_render_target_->DrawRectangle(rectangle, brush);
    brush->Release();
    
    d2d_render_target_->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Graphics::DrawSolidBox(b2Vec2 center, b2Vec2 size, float angle, b2Color color)
{
    const float half_size_x = size.x / 2.f;
    const float half_size_y = size.y / 2.f;

    const D2D1_RECT_F rectangle = D2D1::RectF(
        center.x - half_size_x,
        center.y - half_size_y,
        center.x + half_size_x,
        center.y + half_size_y
    );

    const D2D_COLOR_F d2d_color = D2D1::ColorF(color.r,
                                               color.g,
                                               color.b,
                                               color.a);

    ID2D1SolidColorBrush* brush;
    d2d_render_target_->CreateSolidColorBrush(d2d_color, &brush);

    // 라디안을 각도로 변환
    angle = angle * 180.f / b2_pi;

    D2D1_POINT_2F point = D2D1::Point2F(center.x, center.y);
    d2d_render_target_->SetTransform(D2D1::Matrix3x2F::Rotation(angle, point));

    d2d_render_target_->FillRectangle(rectangle, brush);
    brush->Release();
    
    d2d_render_target_->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Graphics::DrawCircle(b2Vec2 center, float radius, b2Color color)
{
    const D2D1_ELLIPSE ellipse = D2D1::Ellipse(
        D2D1::Point2F(center.x, center.y),
        radius,
        radius
    );
    
    ID2D1SolidColorBrush* brush;
    d2d_render_target_->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &brush);

    d2d_render_target_->DrawEllipse(ellipse, brush);

    brush->Release();
}

void Graphics::DrawSolidCircle(b2Vec2 center, float radius, b2Color color)
{
    const D2D1_ELLIPSE ellipse = D2D1::Ellipse(
        D2D1::Point2F(center.x, center.y),
        radius,
        radius
    );
    
    ID2D1SolidColorBrush* brush;
    d2d_render_target_->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &brush);

    d2d_render_target_->FillEllipse(ellipse, brush);

    brush->Release();
}

void Graphics::DrawPolygon(const b2Vec2* kVertices, int32 vertex_count, b2Color color)
{
    ID2D1PathGeometry* geometry;
    d2d_factory_->CreatePathGeometry(&geometry);

    ID2D1GeometrySink* sink;
    geometry->Open(&sink);

    sink->BeginFigure(D2D1::Point2F(kVertices[0].x, kVertices[0].y), D2D1_FIGURE_BEGIN_FILLED);
    for (int32 i = 1; i < vertex_count; ++i)
    {
        sink->AddLine(D2D1::Point2F(kVertices[i].x, kVertices[i].y));
    }

    sink->EndFigure(D2D1_FIGURE_END_CLOSED);
    sink->Close();
    
    ID2D1SolidColorBrush* brush;
    d2d_render_target_->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &brush);

    d2d_render_target_->DrawGeometry(geometry, brush);

    brush->Release();
}

void Graphics::DrawSolidPolygon(const b2Vec2* kVertices, int32 vertex_count, b2Color color)
{
    ID2D1PathGeometry* geometry;
    d2d_factory_->CreatePathGeometry(&geometry);

    ID2D1GeometrySink* sink;
    geometry->Open(&sink);

    sink->BeginFigure(D2D1::Point2F(kVertices[0].x, kVertices[0].y), D2D1_FIGURE_BEGIN_FILLED);
    for (int32 i = 1; i < vertex_count; ++i)
    {
        sink->AddLine(D2D1::Point2F(kVertices[i].x, kVertices[i].y));
    }

    sink->EndFigure(D2D1_FIGURE_END_CLOSED);
    sink->Close();
    
    ID2D1SolidColorBrush* brush;
    d2d_render_target_->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &brush);

    d2d_render_target_->FillGeometry(geometry, brush);

    brush->Release();
}

void Graphics::DrawTexture(ID2D1Bitmap* texture, b2Vec2 center, b2Vec2 scale, float angle, float opacity)
{
    const float half_size_x = texture->GetSize().width * scale.x / 2.f;
    const float half_size_y = texture->GetSize().height * scale.y / 2.f;

    const D2D1_RECT_F rectangle = D2D1::RectF(
        center.x - half_size_x,
        center.y - half_size_y,
        center.x + half_size_x,
        center.y + half_size_y
    );
    
    angle = angle * 180.f / b2_pi;

    const D2D1_POINT_2F point = D2D1::Point2F(center.x, center.y);
    D2D1_MATRIX_3X2_F transform = D2D1::Matrix3x2F::Rotation(angle, point);
    transform = transform * D2D1::Matrix3x2F::Scale(1.f, 1.f, point);
    d2d_render_target_->SetTransform(transform);

    d2d_render_target_->DrawBitmap(
        texture,
        rectangle,
        opacity,
        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        D2D1::RectF(0, 0, texture->GetSize().width, texture->GetSize().height
        ));

    d2d_render_target_->SetTransform(D2D1::Matrix3x2F::Identity());
}

ID2D1Bitmap* Graphics::LoadTexture(const WCHAR* kFileName)
{
    IWICImagingFactory* wic_factory;
    HRESULT result = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&wic_factory)
    );

    if (FAILED(result))
    {
        return nullptr;
    }

    IWICBitmapDecoder* wic_decoder;
    result = wic_factory->CreateDecoderFromFilename(
        kFileName,
        nullptr,
        GENERIC_READ,
        WICDecodeMetadataCacheOnDemand,
        &wic_decoder
    );

    if (FAILED(result))
    {
        return nullptr;
    }

    IWICBitmapFrameDecode* wic_frame;
    result = wic_decoder->GetFrame(0, &wic_frame);

    if (FAILED(result))
    {
        return nullptr;
    }

    IWICFormatConverter* wic_converter;
    result = wic_factory->CreateFormatConverter(&wic_converter);

    if (FAILED(result))
    {
        return nullptr;
    }

    result = wic_converter->Initialize(
        wic_frame,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        nullptr,
        0.f,
        WICBitmapPaletteTypeMedianCut
    );

    if (FAILED(result))
    {
        return nullptr;
    }

    ID2D1Bitmap* d2d_bitmap;
    result = d2d_render_target_->CreateBitmapFromWicBitmap(
        wic_converter,
        nullptr,
        &d2d_bitmap
    );

    if (FAILED(result))
    {
        return nullptr;
    }

    wic_frame->Release();
    wic_decoder->Release();
    wic_converter->Release();
    wic_factory->Release();

    return d2d_bitmap;
}
