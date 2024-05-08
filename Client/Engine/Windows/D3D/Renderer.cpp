#include "Renderer.h"

#include <cassert>
#include <vector>

#include "Vertex.h"
#include "Shaders.h"
#include "Math/Vector2.h"
#include "Misc/EngineMacros.h"
#include "Windows/WindowsWindow.h"

Microsoft::WRL::ComPtr<ID3D11Device> g_d3d_device;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> g_d3d_device_context;

Renderer* g_renderer = nullptr;

Renderer::Renderer() :
    viewports_(),
    current_viewport_(nullptr)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Init()
{
    if (!CreateDevice()) return false;

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
        g_d3d_device.GetAddressOf(),
        nullptr,
        g_d3d_device_context.GetAddressOf()
    );

    if (FAILED(hr)) return false;
    
    return true;
}

bool Renderer::CreateViewport(SharedPtr<WindowsWindow> window, Math::Vector2 window_size)
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
    swap_chain_desc.BufferCount = 1;
    swap_chain_desc.OutputWindow = window->GetHWnd();
    swap_chain_desc.Windowed = TRUE;
    swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swap_chain_desc.Flags = 0;

    Microsoft::WRL::ComPtr<IDXGIDevice> dxgi_device;
    HRESULT hr = g_d3d_device->QueryInterface(__uuidof(IDXGIDevice),
                                             reinterpret_cast<void**>(dxgi_device.GetAddressOf()));
    if (FAILED(hr)) return false;

    Microsoft::WRL::ComPtr<IDXGIAdapter> dxgi_adapter;
    hr = dxgi_device->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(dxgi_adapter.GetAddressOf()));
    if (FAILED(hr)) return false;

    Microsoft::WRL::ComPtr<IDXGIFactory> dxgi_factory;
    hr = dxgi_adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(dxgi_factory.GetAddressOf()));
    if (FAILED(hr)) return false;

    Viewport viewport;
    hr = dxgi_factory->CreateSwapChain(g_d3d_device.Get(), &swap_chain_desc, viewport.dxgi_swap_chain.GetAddressOf());
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

    HRESULT hr = g_d3d_device->CreateTexture2D(&depth_stencil_desc, nullptr, depth_stencil_buffer.GetAddressOf());
    if (FAILED(hr)) return false;

    hr = g_d3d_device->CreateDepthStencilView(depth_stencil_buffer.Get(), nullptr,
                                             viewport.depth_stencil_view.GetAddressOf());
    return SUCCEEDED(hr);
}

Viewport* Renderer::FindViewport(WindowsWindow* window)
{
    const auto it = viewports_.find(window);
    if (it == viewports_.end()) return nullptr;

    return &it->second;
}

void Renderer::BeginRender(const SharedPtr<WindowsWindow>& kWindow)
{
    current_viewport_ = FindViewport(kWindow.get());
    CHECK_IF(current_viewport_, L"Not found viewport for window.");

    constexpr float clear_color[4] = {0.f, 0.f, 0.f, 1.f};
    g_d3d_device_context->ClearRenderTargetView(current_viewport_->d3d_render_target_view.Get(), clear_color);
    g_d3d_device_context->ClearDepthStencilView(current_viewport_->depth_stencil_view.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
    g_d3d_device_context->RSSetViewports(1, &current_viewport_->d3d_viewport);

    ID3D11RenderTargetView* render_target_view = current_viewport_->d3d_render_target_view.Get();
    ID3D11DepthStencilView* depth_stencil_view = current_viewport_->depth_stencil_view.Get();

    g_d3d_device_context->OMSetRenderTargets(1, &render_target_view, depth_stencil_view);
}

void Renderer::EndRender()
{
    CHECK_IF(current_viewport_, L"Not Set current viewport.");
    
    g_d3d_device_context->OMSetRenderTargets(0, nullptr, nullptr);
    current_viewport_->dxgi_swap_chain->Present(1, 0);

    current_viewport_ = nullptr;
}

bool Renderer::CreateBackBufferResources(Microsoft::WRL::ComPtr<IDXGISwapChain>& dxgi_swap_chain,
                                         Microsoft::WRL::ComPtr<ID3D11Texture2D>& back_buffer,
                                         Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& d3d_render_target_view)
{
    HRESULT hr = dxgi_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D),
                                            reinterpret_cast<void**>(back_buffer.GetAddressOf()));
    if (FAILED(hr)) return false;

    hr = g_d3d_device->CreateRenderTargetView(back_buffer.Get(), nullptr, d3d_render_target_view.GetAddressOf());
    return SUCCEEDED(hr);
}
