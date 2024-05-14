﻿#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include <d3d11.h>
#include <DirectXMath.h>
#include <map>
#include <wrl/client.h>

#include "Math/MathTypes.h"
#include "Misc/EngineMacros.h"

class DefaultPixelShader;
class DefaultVertexShader;

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

    DirectX::XMMATRIX view_matrix;
    DirectX::XMMATRIX projection_matrix;
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
    bool CreateViewport(SHARED_PTR<WindowsWindow> window, Math::Vector2 window_size);
    bool CreateDepthStencilBuffer(Viewport& viewport);
    bool ResizeViewport(const SHARED_PTR<WindowsWindow>& window, MathTypes::uint32 width, MathTypes::uint32 height);

    Viewport* FindViewport(WindowsWindow* window);

    void BeginRender(const SHARED_PTR<WindowsWindow>& kWindow);
    void EndRender();

private:
    bool CreateBackBufferResources(Microsoft::WRL::ComPtr<IDXGISwapChain>& dxgi_swap_chain, Microsoft::WRL::ComPtr<ID3D11Texture2D>& back_buffer, Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& d3d_render_target_view);
    
    std::map<WindowsWindow*, Viewport> viewports_;
    Viewport* current_viewport_;
    
};

extern Renderer* g_renderer;