#define STB_IMAGE_IMPLEMENTATION

#include "Graphics.h"

#include <iostream>

#include "Core.h"
#include "box2d/b2_math.h"

#include <wincodec.h>

#include "ConstantBufferTypes.h"
#include "Vertex.h"
#include "DirectXTK/WICTextureLoader.h"

Graphics::Graphics() :
    d3d_device_(nullptr),
    d3d_device_context_(nullptr),
    d3d_render_target_view_(nullptr),
    dxgi_swap_chain_(nullptr),
    d2d_factory_(nullptr),
    d2d_render_target_(nullptr)
{
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

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        feature_levels,
        2,
        D3D11_SDK_VERSION,
        &swap_chain_desc,
        dxgi_swap_chain_.GetAddressOf(),
        d3d_device_.GetAddressOf(),
        nullptr,
        d3d_device_context_.GetAddressOf()
    );

    if (FAILED(hr)) return false;
    return InitRenderTargetD3D();
}

bool Graphics::InitRenderTargetD3D()
{
    ID3D11Texture2D* back_buffer;

    HRESULT hr = dxgi_swap_chain_->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
    if (FAILED(hr)) return false;

    hr = d3d_device_->CreateRenderTargetView(back_buffer, nullptr, &d3d_render_target_view_);
    back_buffer->Release();
    
    if (FAILED(hr)) return false;

    D3D11_TEXTURE2D_DESC depth_stencil_desc;
    depth_stencil_desc.Width = Core::Get()->GetResolution().x;
    depth_stencil_desc.Height = Core::Get()->GetResolution().y;
    depth_stencil_desc.MipLevels = 1;
    depth_stencil_desc.ArraySize = 1;
    depth_stencil_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depth_stencil_desc.SampleDesc.Count = 1;
    depth_stencil_desc.SampleDesc.Quality = 0;
    depth_stencil_desc.Usage = D3D11_USAGE_DEFAULT;
    depth_stencil_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depth_stencil_desc.CPUAccessFlags = 0;
    depth_stencil_desc.MiscFlags = 0;

    hr = d3d_device_->CreateTexture2D(&depth_stencil_desc, nullptr, depth_stencil_buffer_.GetAddressOf());
    if (FAILED(hr)) return false;

    hr = d3d_device_->CreateDepthStencilView(depth_stencil_buffer_.Get(), nullptr, depth_stencil_view_.GetAddressOf());
    if (FAILED(hr)) return false;
    
    d3d_device_context_->OMSetRenderTargets(1, d3d_render_target_view_.GetAddressOf(), depth_stencil_view_.Get());

    D3D11_DEPTH_STENCIL_DESC depth_stencil_state_desc;
    ZeroMemory(&depth_stencil_state_desc, sizeof(D3D11_DEPTH_STENCIL_DESC));

    depth_stencil_state_desc.DepthEnable = true;
    depth_stencil_state_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depth_stencil_state_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

    hr = d3d_device_->CreateDepthStencilState(&depth_stencil_state_desc, depth_stencil_state_.GetAddressOf());
    if (FAILED(hr)) return false;

    d3d_viewport_.TopLeftX = 0;
    d3d_viewport_.TopLeftY = 0;
    d3d_viewport_.Width = static_cast<float>(Core::Get()->GetResolution().x);
    d3d_viewport_.Height = static_cast<float>(Core::Get()->GetResolution().y);
    d3d_viewport_.MinDepth = 0.0f;
    d3d_viewport_.MaxDepth = 1.0f;
    
    d3d_device_context_->RSSetViewports(1, &d3d_viewport_);

    D3D11_RASTERIZER_DESC rasterizer_desc;
    ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));

    rasterizer_desc.FillMode = D3D11_FILL_SOLID;
    rasterizer_desc.CullMode = D3D11_CULL_NONE;

    hr = d3d_device_->CreateRasterizerState(&rasterizer_desc, rasterizer_state_.GetAddressOf());
    if (FAILED(hr)) return false;

    D3D11_SAMPLER_DESC sampler_desc;
    ZeroMemory(&sampler_desc, sizeof(D3D11_SAMPLER_DESC));
    sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampler_desc.MinLOD = 0;
    sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

    hr = d3d_device_->CreateSamplerState(&sampler_desc, sampler_state_.GetAddressOf());
    if (FAILED(hr)) return false;

    return InitShaders();
}

bool Graphics::InitShaders()
{
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    constexpr UINT num_elements = ARRAYSIZE(layout);
    if (!vertex_shader_.Init(d3d_device_, L"..\\x64\\Debug\\VertexShader.cso", layout, num_elements)) return false;
    if (!pixel_shader_.Init(d3d_device_, L"..\\x64\\Debug\\PixelShader.cso")) return false;
    
    return InitScene();
}

bool Graphics::InitScene()
{
    Vertex vertices[] = {
        {-.5f, -.5f, 0.f, 0.f, 1.f},
        {-.5f, .5f, 0.f, 0.f, 0.f},
        {.5f, .5f, 0.f, 1.f, 0.f},
        {.5f, -.5f, 0.f, 1.f, 1.f}
    };

    DWORD indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    HRESULT hr = vertex_buffer_.Init(d3d_device_.Get(), vertices, ARRAYSIZE(vertices));
    if (FAILED(hr)) return false;

    hr = index_buffer_.Init(d3d_device_.Get(), indices, ARRAYSIZE(indices));
    if (FAILED(hr)) return false;

    hr = DirectX::CreateWICTextureFromFile(d3d_device_.Get(), L".\\box.png", nullptr, texture_.GetAddressOf());
    if (FAILED(hr)) return false;

    hr = constant_buffer_.Init(d3d_device_.Get(), d3d_device_context_.Get());
    if (FAILED(hr)) return false;

    camera_.SetPosition(0.f, 0.f, -2.f);
    camera_.SetProjectionValues(90.f, static_cast<float>(Core::Get()->GetResolution().x) / static_cast<float>(Core::Get()->GetResolution().y), 0.1f, 1000.f);
    
    return true;
}

bool Graphics::InitFactoryD2D()
{
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, d2d_factory_.GetAddressOf());

    if (FAILED(hr)) return false;
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

    HRESULT hr = dxgi_swap_chain_->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
    if (FAILED(hr)) return false;

    hr = d2d_factory_->CreateDxgiSurfaceRenderTarget(back_buffer, &render_target_properties, &d2d_render_target_);
    back_buffer->Release();

    return SUCCEEDED(hr);
}

void Graphics::BeginRenderD3D()
{
    constexpr float clear_color[] = {0.f, 0.f, 0.f, 1.f};
    d3d_device_context_->ClearRenderTargetView(d3d_render_target_view_.Get(), clear_color);
    d3d_device_context_->ClearDepthStencilView(depth_stencil_view_.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

    d3d_device_context_->IASetInputLayout(vertex_shader_.GetInputLayout());
    d3d_device_context_->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    d3d_device_context_->RSSetState(rasterizer_state_.Get());
    d3d_device_context_->OMSetDepthStencilState(depth_stencil_state_.Get(), 0);
    d3d_device_context_->PSSetSamplers(0, 1, sampler_state_.GetAddressOf());
    d3d_device_context_->VSSetShader(vertex_shader_.GetShader(), nullptr, 0);
    d3d_device_context_->PSSetShader(pixel_shader_.GetShader(), nullptr, 0);

    constexpr UINT offset = 0;

    DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
    
    constant_buffer_.data.mat = world * camera_.GetViewMatrix() * camera_.GetProjectionMatrix();
    constant_buffer_.data.mat = DirectX::XMMatrixTranspose(constant_buffer_.data.mat);
    
    if (!constant_buffer_.ApplyChanges()) return;
    d3d_device_context_->VSSetConstantBuffers(0, 1, constant_buffer_.GetAddressOf());

    d3d_device_context_->PSSetShaderResources(0, 1, texture_.GetAddressOf());
    d3d_device_context_->IASetVertexBuffers(0, 1, vertex_buffer_.GetAddressOf(), vertex_buffer_.StridePtr(), &offset);
    d3d_device_context_->IASetIndexBuffer(index_buffer_.Get(), DXGI_FORMAT_R32_UINT, 0);
    d3d_device_context_->DrawIndexed(index_buffer_.BufferSize(), 0, 0);
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
    HRESULT hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&wic_factory)
    );

    if (FAILED(hr))
    {
        return nullptr;
    }

    IWICBitmapDecoder* wic_decoder;
    hr = wic_factory->CreateDecoderFromFilename(
        kFileName,
        nullptr,
        GENERIC_READ,
        WICDecodeMetadataCacheOnDemand,
        &wic_decoder
    );

    if (FAILED(hr))
    {
        return nullptr;
    }

    IWICBitmapFrameDecode* wic_frame;
    hr = wic_decoder->GetFrame(0, &wic_frame);

    if (FAILED(hr))
    {
        return nullptr;
    }

    IWICFormatConverter* wic_converter;
    hr = wic_factory->CreateFormatConverter(&wic_converter);

    if (FAILED(hr))
    {
        return nullptr;
    }

    hr = wic_converter->Initialize(
        wic_frame,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        nullptr,
        0.f,
        WICBitmapPaletteTypeMedianCut
    );

    if (FAILED(hr))
    {
        return nullptr;
    }

    ID2D1Bitmap* d2d_bitmap;
    hr = d2d_render_target_->CreateBitmapFromWicBitmap(
        wic_converter,
        nullptr,
        &d2d_bitmap
    );

    if (FAILED(hr))
    {
        return nullptr;
    }

    wic_frame->Release();
    wic_decoder->Release();
    wic_converter->Release();
    wic_factory->Release();

    return d2d_bitmap;
}
