#pragma once
#include <d3d11.h>
#include <map>
#include <memory>
#include <wrl/client.h>

class RenderingPolicy;

namespace Math
{
    struct Vector2;
}

class WindowsWindow;

struct Viewport
{
    Microsoft::WRL::ComPtr<IDXGISwapChain> dxgi_swap_chain;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> d3d_render_target_view;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view;
    
    D3D11_VIEWPORT d3d_viewport;
};

extern Microsoft::WRL::ComPtr<ID3D11Device> g_d3d_device;
extern Microsoft::WRL::ComPtr<ID3D11DeviceContext> g_d3d_device_context;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool Init();
    bool CreateDevice();
    bool CreateViewport(std::shared_ptr<WindowsWindow> window, Math::Vector2 window_size);
    bool CreateDepthStencilBuffer(Viewport& viewport);

private:
    bool CreateBackBufferResources(Microsoft::WRL::ComPtr<IDXGISwapChain>& dxgi_swap_chain, Microsoft::WRL::ComPtr<ID3D11Texture2D>& back_buffer, Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& d3d_render_target_view);

    std::shared_ptr<RenderingPolicy> rendering_policy_;
    
    std::map<WindowsWindow*, Viewport> viewports_;
    
};
