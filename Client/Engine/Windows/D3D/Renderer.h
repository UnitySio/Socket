#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include <d3d11.h>
#include <d2d1.h>
#include <DirectXMath.h>
#include <map>
#include <wrl/client.h>

#include "Singleton.h"
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

struct D2DViewport
{
    Microsoft::WRL::ComPtr<ID2D1RenderTarget> d2d_render_target;
};

class Renderer : public Singleton<Renderer>
{
public:
    Renderer();
    virtual ~Renderer() override;

    bool Init();
    bool CreateDevice();
    bool CreateD2DFactory();
    bool CreateViewport(SHARED_PTR<WindowsWindow> window, Math::Vector2 window_size);
    bool CreateD2DViewport(SHARED_PTR<WindowsWindow> window);
    bool CreateDepthStencilBuffer(Viewport& viewport);
    bool ResizeViewport(const SHARED_PTR<WindowsWindow>& window, MathTypes::uint32 width, MathTypes::uint32 height);

    Viewport* FindViewport(WindowsWindow* window);
    D2DViewport* FindD2DViewport(WindowsWindow* window);

    void BeginRender(const SHARED_PTR<WindowsWindow>& kWindow);
    void EndRender();
    void BeginRenderD2D(const SHARED_PTR<WindowsWindow>& kWindow);
    void EndRenderD2D();

    inline ID3D11Device* GetDevice() const { return d3d_device_.Get(); }
    inline ID3D11DeviceContext* GetDeviceContext() const { return d3d_device_context_.Get(); }

private:
    bool CreateBackBufferResources(Microsoft::WRL::ComPtr<IDXGISwapChain>& dxgi_swap_chain, Microsoft::WRL::ComPtr<ID3D11Texture2D>& back_buffer, Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& d3d_render_target_view);

    Microsoft::WRL::ComPtr<ID3D11Device> d3d_device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3d_device_context_;

    Microsoft::WRL::ComPtr<ID2D1Factory> d2d_factory_;
    
    std::map<WindowsWindow*, Viewport> viewports_;
    std::map<WindowsWindow*, D2DViewport> d2d_viewports_;
    
    Viewport* current_viewport_;
    D2DViewport* current_d2d_viewport_;
    
};
