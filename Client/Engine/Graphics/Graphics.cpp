#define STB_IMAGE_IMPLEMENTATION

#include "Graphics.h"

#include <iostream>

#include "Windows/WindowsApplication.h"

#include "ProjectSettings.h"
#include "Windows/WindowsWindow.h"

Graphics::Graphics() :
    d3d_device_(nullptr),
    d3d_device_context_(nullptr),
    d3d_render_target_view_(nullptr),
    dxgi_swap_chain_(nullptr),
    d2d_factory_(nullptr),
    d2d_render_target_(nullptr)
{
}

bool Graphics::Init(const std::shared_ptr<WindowsWindow>& window)
{
    window_ = window;
    return InitDeviceD3D() && InitFactoryD2D();
}

bool Graphics::InitDeviceD3D()
{
    DXGI_SWAP_CHAIN_DESC swap_chain_desc;
    ZeroMemory(&swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));

    swap_chain_desc.BufferDesc.Width = 640;
    swap_chain_desc.BufferDesc.Height = 480;
    swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
    swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    
    swap_chain_desc.SampleDesc.Count = 1;
    swap_chain_desc.SampleDesc.Quality = 0;
    
    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.BufferCount = 1;
    swap_chain_desc.OutputWindow = window_->GetHWnd();
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
    Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer;

    HRESULT hr = dxgi_swap_chain_->GetBuffer(0, IID_PPV_ARGS(back_buffer.GetAddressOf()));
    if (FAILED(hr)) return false;

    hr = d3d_device_->CreateRenderTargetView(back_buffer.Get(), nullptr, &d3d_render_target_view_);
    if (FAILED(hr)) return false;

    D3D11_TEXTURE2D_DESC depth_stencil_desc;
    depth_stencil_desc.Width = 640;
    depth_stencil_desc.Height = 480;
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
    d3d_viewport_.Width = 640;
    d3d_viewport_.Height = 480;
    d3d_viewport_.MinDepth = 0.0f;
    d3d_viewport_.MaxDepth = 1.0f;

    d3d_device_context_->RSSetViewports(1, &d3d_viewport_);

    D3D11_RASTERIZER_DESC rasterizer_desc;
    ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));

    rasterizer_desc.FillMode = D3D11_FILL_SOLID;
    rasterizer_desc.CullMode = D3D11_CULL_NONE;

    hr = d3d_device_->CreateRasterizerState(&rasterizer_desc, rasterizer_state_.GetAddressOf());
    if (FAILED(hr)) return false;

    D3D11_BLEND_DESC blend_desc;
    ZeroMemory(&blend_desc, sizeof(D3D11_BLEND_DESC));

    D3D11_RENDER_TARGET_BLEND_DESC render_target_blend_desc;
    ZeroMemory(&render_target_blend_desc, sizeof(D3D11_RENDER_TARGET_BLEND_DESC));

    render_target_blend_desc.BlendEnable = true;
    render_target_blend_desc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    render_target_blend_desc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    render_target_blend_desc.BlendOp = D3D11_BLEND_OP_ADD;
    render_target_blend_desc.SrcBlendAlpha = D3D11_BLEND_ONE;
    render_target_blend_desc.DestBlendAlpha = D3D11_BLEND_ZERO;
    render_target_blend_desc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    render_target_blend_desc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    blend_desc.RenderTarget[0] = render_target_blend_desc;

    hr = d3d_device_->CreateBlendState(&blend_desc, blend_state_.GetAddressOf());
    if (FAILED(hr)) return false;

    D3D11_SAMPLER_DESC sampler_desc;
    ZeroMemory(&sampler_desc, sizeof(D3D11_SAMPLER_DESC));
    sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // D3D11_FILTER_MIN_MAG_MIP_LINEAR;
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
    return InitScene();
}

bool Graphics::InitScene()
{
    camera_2d_.SetProjectionValues(5.f, .3f, 1000.f);

    sprite_batch_ = std::make_unique<SpriteBatch>(d3d_device_context_.Get());

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
    const float kDPI = GetDpiForWindow(window_->GetHWnd());
    const D2D1_RENDER_TARGET_PROPERTIES render_target_properties = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
        kDPI,
        kDPI
    );

    Microsoft::WRL::ComPtr<IDXGISurface> back_buffer;

    HRESULT hr = dxgi_swap_chain_->GetBuffer(0, IID_PPV_ARGS(back_buffer.GetAddressOf()));
    if (FAILED(hr)) return false;

    hr = d2d_factory_->CreateDxgiSurfaceRenderTarget(back_buffer.Get(), &render_target_properties, &d2d_render_target_);
    return SUCCEEDED(hr);
}

void Graphics::BeginFrame3D()
{
    constexpr float clear_color[4] = {
        49.f / 255.f,
        77.f / 255.f,
        121.f / 255.f,
        1.f
    };

    d3d_device_context_->ClearRenderTargetView(d3d_render_target_view_.Get(), clear_color);
    d3d_device_context_->ClearDepthStencilView(depth_stencil_view_.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

    d3d_device_context_->RSSetState(rasterizer_state_.Get());
    d3d_device_context_->OMSetDepthStencilState(depth_stencil_state_.Get(), 0);
    d3d_device_context_->OMSetBlendState(blend_state_.Get(), nullptr, 0xffffffff);
    d3d_device_context_->PSSetSamplers(0, 1, sampler_state_.GetAddressOf());

    sprite_batch_->Begin(camera_2d_.GetWorldMatrix() * camera_2d_.GetOrthographicMatrix());
}

void Graphics::EndFrame3D()
{
    sprite_batch_->End();
    if (dxgi_swap_chain_->Present(1, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED) return;
    dxgi_swap_chain_->Present(ProjectSettings::kUseVSync ? 1 : 0, 0);
}
