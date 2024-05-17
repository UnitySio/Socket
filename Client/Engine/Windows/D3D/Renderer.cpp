﻿#include "Renderer.h"

#include <algorithm>
#include <cassert>
#include <vector>

#include "ProjectSettings.h"
#include "Vertex.h"
#include "Shaders.h"
#include "imgui/imgui.h"
#include "Math/Vector2.h"
#include "Misc/EngineMacros.h"
#include "Windows/WindowsWindow.h"

Renderer::Renderer() :
    d3d_device_(nullptr),
    d3d_device_context_(nullptr),
    d2d_factory_(nullptr),
    viewports_(),
    d2d_viewports_(),
    current_viewport_(nullptr),
    current_d2d_viewport_(nullptr)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Init()
{
    if (!CreateDevice()) return false;
    if (!CreateD2DFactory()) return false;

    return true;
}

bool Renderer::CreateDevice()
{
    constexpr D3D_FEATURE_LEVEL feature_levels[] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1
    };

    HRESULT hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        feature_levels,
        ARRAYSIZE(feature_levels),
        D3D11_SDK_VERSION,
        d3d_device_.GetAddressOf(),
        nullptr,
        d3d_device_context_.GetAddressOf()
    );

    if (FAILED(hr)) return false;
    
    return true;
}

bool Renderer::CreateD2DFactory()
{
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, d2d_factory_.GetAddressOf());
    return SUCCEEDED(hr);
}

bool Renderer::CreateViewport(SHARED_PTR<WindowsWindow> window, Math::Vector2 window_size)
{
    DXGI_SWAP_CHAIN_DESC swap_chain_desc;
    ZeroMemory(&swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));

    swap_chain_desc.BufferDesc.Width = window_size.x;
    swap_chain_desc.BufferDesc.Height = window_size.y;
    swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
    swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    swap_chain_desc.SampleDesc.Count = 1;
    swap_chain_desc.SampleDesc.Quality = 0;

    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.BufferCount = 2;
    swap_chain_desc.OutputWindow = window->GetHWnd();
    swap_chain_desc.Windowed = TRUE;
    swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swap_chain_desc.Flags = 0;

    Microsoft::WRL::ComPtr<IDXGIDevice> dxgi_device;
    HRESULT hr = d3d_device_->QueryInterface(IID_PPV_ARGS(dxgi_device.GetAddressOf()));
    if (FAILED(hr)) return false;

    Microsoft::WRL::ComPtr<IDXGIAdapter> dxgi_adapter;
    hr = dxgi_device->GetParent(IID_PPV_ARGS(dxgi_adapter.GetAddressOf()));
    if (FAILED(hr)) return false;

    Microsoft::WRL::ComPtr<IDXGIFactory> dxgi_factory;
    hr = dxgi_adapter->GetParent(IID_PPV_ARGS(dxgi_factory.GetAddressOf()));
    if (FAILED(hr)) return false;

    Viewport viewport;
    
    hr = dxgi_factory->CreateSwapChain(d3d_device_.Get(), &swap_chain_desc, viewport.dxgi_swap_chain.GetAddressOf());
    if (FAILED(hr)) return false;

    // Alt + Enter 키를 눌러 전체 화면으로 전환하는 기능을 비활성화
    hr = dxgi_factory->MakeWindowAssociation(window->GetHWnd(), DXGI_MWA_NO_ALT_ENTER);
    if (FAILED(hr)) return false;

    viewport.d3d_viewport.TopLeftX = 0;
    viewport.d3d_viewport.TopLeftY = 0;
    viewport.d3d_viewport.Width = window_size.x;
    viewport.d3d_viewport.Height = window_size.y;
    viewport.d3d_viewport.MinDepth = 0.0f;
    viewport.d3d_viewport.MaxDepth = 1.0f;

    hr = CreateBackBufferResources(viewport.dxgi_swap_chain, viewport.back_buffer, viewport.d3d_render_target_view);
    if (FAILED(hr)) return false;

    viewport.view_matrix = DirectX::XMMatrixIdentity();
    viewport.projection_matrix = DirectX::XMMatrixOrthographicOffCenterLH(0.f, window_size.x, window_size.y, 0.f, 0.f, 1.f);

    viewports_[window.get()] = viewport;
    return true;
}

bool Renderer::CreateD2DViewport(std::shared_ptr<WindowsWindow> window)
{
    Viewport* viewport = FindViewport(window.get());
    if (viewport)
    {
        const MathTypes::uint32 kDPI = GetDpiForWindow(window->GetHWnd());
        const D2D1_RENDER_TARGET_PROPERTIES render_target_properties = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
            kDPI,
            kDPI
        );

        Microsoft::WRL::ComPtr<IDXGISurface> dxgi_back_buffer;
        HRESULT hr = viewport->dxgi_swap_chain->GetBuffer(0, IID_PPV_ARGS(dxgi_back_buffer.GetAddressOf()));
        if (FAILED(hr)) return false;

        D2DViewport d2d_viewport;
        hr = d2d_factory_->CreateDxgiSurfaceRenderTarget(dxgi_back_buffer.Get(), &render_target_properties, d2d_viewport.d2d_render_target.GetAddressOf());
        if (FAILED(hr)) return false;

        d2d_viewports_[window.get()] = d2d_viewport;

        return true;
    }

    return false;
}

bool Renderer::CreateDepthStencilBuffer(Viewport& viewport)
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> depth_stencil_buffer;

    D3D11_TEXTURE2D_DESC depth_stencil_desc;
    ZeroMemory(&depth_stencil_desc, sizeof(D3D11_TEXTURE2D_DESC));

    depth_stencil_desc.Width = viewport.d3d_viewport.Width;
    depth_stencil_desc.Height = viewport.d3d_viewport.Height;
    depth_stencil_desc.MipLevels = 1;
    depth_stencil_desc.ArraySize = 1;
    depth_stencil_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depth_stencil_desc.SampleDesc.Count = 1;
    depth_stencil_desc.SampleDesc.Quality = 0;
    depth_stencil_desc.Usage = D3D11_USAGE_DEFAULT;
    depth_stencil_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depth_stencil_desc.CPUAccessFlags = 0;
    depth_stencil_desc.MiscFlags = 0;

    HRESULT hr = d3d_device_->CreateTexture2D(&depth_stencil_desc, nullptr, depth_stencil_buffer.GetAddressOf());
    if (FAILED(hr)) return false;

    hr = d3d_device_->CreateDepthStencilView(depth_stencil_buffer.Get(), nullptr,
                                             viewport.depth_stencil_view.GetAddressOf());
    return SUCCEEDED(hr);
}

bool Renderer::ResizeViewport(const std::shared_ptr<WindowsWindow>& window, MathTypes::uint32 width, MathTypes::uint32 height)
{
    Viewport* viewport = FindViewport(window.get());
    if (viewport && (viewport->d3d_viewport.Width != width || viewport->d3d_viewport.Height != height))
    {
        d3d_device_context_->OMSetRenderTargets(0, nullptr, nullptr);
        d3d_device_context_->ClearState();
        d3d_device_context_->Flush();
        
        D2DViewport* d2d_viewport = FindD2DViewport(window.get());
        if (d2d_viewport) d2d_viewport->d2d_render_target.Reset();
        
        viewport->back_buffer.Reset();
        viewport->d3d_render_target_view.Reset();
        viewport->depth_stencil_view.Reset();

        viewport->d3d_viewport.Width = width;
        viewport->d3d_viewport.Height = height;

        DXGI_SWAP_CHAIN_DESC swap_chain_desc;
        HRESULT hr = viewport->dxgi_swap_chain->GetDesc(&swap_chain_desc);
        if (FAILED(hr)) return false;

        hr = viewport->dxgi_swap_chain->ResizeBuffers(swap_chain_desc.BufferCount, width, height, swap_chain_desc.BufferDesc.Format, swap_chain_desc.Flags);
        if (FAILED(hr)) return false;

        if (!CreateBackBufferResources(viewport->dxgi_swap_chain, viewport->back_buffer, viewport->d3d_render_target_view)) return false;

#pragma region D2D Resize
        const MathTypes::uint32 kDPI = GetDpiForWindow(window->GetHWnd());
        const D2D1_RENDER_TARGET_PROPERTIES render_target_properties = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
            kDPI,
            kDPI
        );

        Microsoft::WRL::ComPtr<IDXGISurface> dxgi_back_buffer;
        hr = viewport->dxgi_swap_chain->GetBuffer(0, IID_PPV_ARGS(dxgi_back_buffer.GetAddressOf()));
        if (FAILED(hr)) return false;

        hr = d2d_factory_->CreateDxgiSurfaceRenderTarget(dxgi_back_buffer.Get(), &render_target_properties, d2d_viewport->d2d_render_target.GetAddressOf());
        return SUCCEEDED(hr);
#pragma endregion
    }

    return false;
}

Viewport* Renderer::FindViewport(WindowsWindow* window)
{
    const auto it = viewports_.find(window);
    if (it == viewports_.end()) return nullptr;

    return &it->second;
}

D2DViewport* Renderer::FindD2DViewport(WindowsWindow* window)
{
    const auto it = d2d_viewports_.find(window);
    if (it == d2d_viewports_.end()) return nullptr;

    return &it->second;
}

void Renderer::BeginRender(const SHARED_PTR<WindowsWindow>& kWindow)
{
    current_viewport_ = FindViewport(kWindow.get());
    CHECK_IF(current_viewport_, L"Not found viewport for window.");

    constexpr float clear_color[4] = {
        49.f / 255.f,
        77.f / 255.f,
        121.f / 255.f,
        1.f
    };
    
    d3d_device_context_->ClearRenderTargetView(current_viewport_->d3d_render_target_view.Get(), clear_color);
    d3d_device_context_->ClearDepthStencilView(current_viewport_->depth_stencil_view.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
    d3d_device_context_->RSSetViewports(1, &current_viewport_->d3d_viewport);

    ID3D11RenderTargetView* render_target_view = current_viewport_->d3d_render_target_view.Get();
    ID3D11DepthStencilView* depth_stencil_view = current_viewport_->depth_stencil_view.Get();

    d3d_device_context_->OMSetRenderTargets(1, &render_target_view, depth_stencil_view);
}

void Renderer::EndRender()
{
    CHECK_IF(current_viewport_, L"Not Set current viewport.");
    
    d3d_device_context_->OMSetRenderTargets(0, nullptr, nullptr);
    current_viewport_->dxgi_swap_chain->Present(ProjectSettings::kUseVSync, 0);

    current_viewport_ = nullptr;
}

void Renderer::BeginRenderD2D(const std::shared_ptr<WindowsWindow>& kWindow)
{
    current_d2d_viewport_ = FindD2DViewport(kWindow.get());
    CHECK_IF(current_d2d_viewport_, L"Not found D2D viewport for window.");

    current_d2d_viewport_->d2d_render_target->BeginDraw();
}

void Renderer::EndRenderD2D()
{
    current_d2d_viewport_->d2d_render_target->EndDraw();
    current_d2d_viewport_ = nullptr;
}

bool Renderer::CreateBackBufferResources(Microsoft::WRL::ComPtr<IDXGISwapChain>& dxgi_swap_chain,
                                         Microsoft::WRL::ComPtr<ID3D11Texture2D>& back_buffer,
                                         Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& d3d_render_target_view)
{
    HRESULT hr = dxgi_swap_chain->GetBuffer(0, IID_PPV_ARGS(back_buffer.GetAddressOf()));
    if (FAILED(hr)) return false;

    hr = d3d_device_->CreateRenderTargetView(back_buffer.Get(), nullptr, d3d_render_target_view.GetAddressOf());
    return SUCCEEDED(hr);
}
