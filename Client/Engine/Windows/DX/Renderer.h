#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include <wrl/client.h>
#include <d3d11.h>
#include <d2d1.h>
#include <dwrite_3.h>
#include <wincodec.h>
#include <DirectXMath.h>
#include <map>

#include "Singleton.h"
#include "Math/MathTypes.h"

class DefaultPixelShader;
class DefaultVertexShader;

namespace Math
{
    struct Vector2;
    struct Color;
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
    virtual ~Renderer() override = default;

    bool Init();
    bool CreateDevice();
    bool CreateDWrite();
    bool CreateViewport(std::shared_ptr<WindowsWindow> window, Math::Vector2 window_size);
    bool CreateD2DViewport(std::shared_ptr<WindowsWindow> window);
    bool CreateDepthStencilBuffer(Viewport& viewport);
    bool ResizeViewport(const std::shared_ptr<WindowsWindow>& window, MathTypes::uint32 width, MathTypes::uint32 height);

    // UI TEST
    D2DViewport* GetCurrentD2dViewport() { return current_d2d_viewport_; }


    
    // TEST
    bool CreateRenderToTexture();

    void BeginRTT();
    void EndRTT();

    inline const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& GetSRV() const { return srv_; }

    Viewport* FindViewport(WindowsWindow* window);
    D2DViewport* FindD2DViewport(WindowsWindow* window);

    void BeginRender(const std::shared_ptr<WindowsWindow>& kWindow);
    void EndRender();
    void BeginRenderD2D(const std::shared_ptr<WindowsWindow>& kWindow);
    void EndRenderD2D();
    void BeginLayer();
    void EndLayer();
    
    Math::Vector2 ConvertScreenToWorld(const Math::Vector2& kScreenPosition) const;
    Math::Vector2 ConvertWorldToScreen(const Math::Vector2& kWorldPosition) const;

    inline ID3D11Device* GetDevice() const { return d3d_device_.Get(); }
    inline ID3D11DeviceContext* GetDeviceContext() const { return d3d_device_context_.Get(); }
    inline Microsoft::WRL::ComPtr<IWICImagingFactory> GetImageFactory() const { return wic_imaging_factory_; }
private:
    bool CreateBackBufferResources(Microsoft::WRL::ComPtr<IDXGISwapChain>& dxgi_swap_chain, Microsoft::WRL::ComPtr<ID3D11Texture2D>& back_buffer, Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& d3d_render_target_view);

    Microsoft::WRL::ComPtr<ID3D11Device> d3d_device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3d_device_context_;

    Microsoft::WRL::ComPtr<ID2D1Factory> d2d_factory_;
    Microsoft::WRL::ComPtr<IWICImagingFactory> wic_imaging_factory_;
    
    std::map<WindowsWindow*, Viewport> viewports_;
    std::map<WindowsWindow*, D2DViewport> d2d_viewports_;
    
    Viewport* current_viewport_;
    D2DViewport* current_d2d_viewport_;

    // TEST
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv_;
    
};
