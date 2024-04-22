#pragma once
#include <d3d11.h>
#include <map>
#include <memory>
#include <wrl/client.h>

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
    
    D3D11_VIEWPORT d3d_viewport;
};

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool CreateDevice();
    bool CreateViewport(std::shared_ptr<WindowsWindow> window, Math::Vector2 window_size);

private:
    bool CreateBackBufferResources(Microsoft::WRL::ComPtr<IDXGISwapChain>& dxgi_swap_chain, Microsoft::WRL::ComPtr<ID3D11Texture2D>& back_buffer, Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& d3d_render_target_view);
    
    Microsoft::WRL::ComPtr<ID3D11Device> d3d_device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3d_device_context_;

    std::map<WindowsWindow*, Viewport> viewports_;
    
};
