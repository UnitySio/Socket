#pragma once
#include <d3d11.h>
#include <map>
#include <memory>
#include <vector>
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

    struct ImGuiContext* imgui_context;
};

extern Microsoft::WRL::ComPtr<ID3D11Device> g_d3d_device;
extern Microsoft::WRL::ComPtr<ID3D11DeviceContext> g_d3d_device_context;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool Init();
    bool InitResources();
    bool CreateDevice();
    bool CreateViewport(std::shared_ptr<WindowsWindow> window, Math::Vector2 window_size);
    bool CreateDepthStencilBuffer(Viewport& viewport);

    Viewport* FindViewport(WindowsWindow* window);

    void DrawWindows(const std::vector<std::shared_ptr<WindowsWindow>>& kWindows);

private:
    bool CreateBackBufferResources(Microsoft::WRL::ComPtr<IDXGISwapChain>& dxgi_swap_chain, Microsoft::WRL::ComPtr<ID3D11Texture2D>& back_buffer, Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& d3d_render_target_view);

    Microsoft::WRL::ComPtr<ID3D11SamplerState> point_sampler_state_wrap_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> bilinear_sampler_state_wrap_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> bilinear_sampler_state_clamp_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> point_sampler_state_clamp_;
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
    
    std::map<WindowsWindow*, Viewport> viewports_;
    
};
