#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#include "Singleton.h"

#include <d3d11.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wrl/client.h>

#include "Camera2D.h"
#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"
#include "Windows/D3D/Shaders.h"
#include "SpriteBatch.h"
#include "box2d/b2_draw.h"

class WindowsWindow;
struct b2Vec2;

class Graphics
{
public:
    Graphics();
    ~Graphics() = default;

    bool Init(const std::shared_ptr<WindowsWindow>& window);
    
    void BeginFrame3D();
    void EndFrame3D();

    inline ID3D11Device* GetD3DDevice() const { return d3d_device_.Get(); }
    inline ID3D11DeviceContext* GetD3DDeviceContext() const { return d3d_device_context_.Get(); }
    inline void BeginFrame2D() const { d2d_render_target_->BeginDraw(); }
    inline void EndFrame2D() const { d2d_render_target_->EndDraw(); }
    inline Camera2D& GetCamera2D() { return camera_2d_; }

    // 테스트 코드
    inline SpriteBatch* GetSpriteBatch() const { return sprite_batch_.get(); }

private:
    bool InitDeviceD3D();
    bool InitRenderTargetD3D();
    bool InitShaders();
    bool InitScene();
    bool InitFactoryD2D();
    bool InitRenderTargetD2D();

    std::shared_ptr<WindowsWindow> window_;
    
    Microsoft::WRL::ComPtr<ID3D11Device> d3d_device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3d_device_context_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> d3d_render_target_view_;
    D3D11_VIEWPORT d3d_viewport_;
    
    Microsoft::WRL::ComPtr<IDXGISwapChain> dxgi_swap_chain_;

    Microsoft::WRL::ComPtr<ID2D1Factory> d2d_factory_;
    Microsoft::WRL::ComPtr<ID2D1RenderTarget> d2d_render_target_;

    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view_;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> depth_stencil_buffer_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
    
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_;
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;

    Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler_state_;

    Camera2D camera_2d_;

    std::unique_ptr<SpriteBatch> sprite_batch_;

    Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer_;
    
};
