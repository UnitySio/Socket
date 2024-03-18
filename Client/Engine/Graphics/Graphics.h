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
#include "Shaders.h"
#include "TempSprite.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "box2d/b2_draw.h"
#include "DirectXTK/PrimitiveBatch.h"

struct b2Vec2;

class Graphics : public Singleton<Graphics>
{
public:
    Graphics();
    virtual ~Graphics() override = default;

    bool Init();
    
    void BeginFrame3D();
    void EndFrame3D();

    void DrawLine(b2Vec2 start, b2Vec2 end, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawBox(b2Vec2 center, b2Vec2 size, float angle, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawSolidBox(b2Vec2 center, b2Vec2 size, float angle, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawCircle(b2Vec2 center, float radius, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawSolidCircle(b2Vec2 center, float radius, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawPolygon(const b2Vec2* kVertices, int32 vertex_count, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawSolidPolygon(const b2Vec2* kVertices, int32 vertex_count, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawTexture(ID2D1Bitmap* texture, b2Vec2 center, b2Vec2 scale = b2Vec2(1.f, 1.f), float angle = 0.f, float opacity = 1.f);

    ID2D1Bitmap* LoadTexture(const WCHAR* kFileName);

    inline ID3D11Device* GetD3DDevice() const { return d3d_device_.Get(); }
    inline ID3D11DeviceContext* GetD3DDeviceContext() const { return d3d_device_context_.Get(); }
    inline void BeginFrame2D() const { d2d_render_target_->BeginDraw(); }
    inline void EndFrame2D() const { d2d_render_target_->EndDraw(); }
    inline Camera2D& GetCamera2D() { return camera_2d_; }

private:
    bool InitDeviceD3D();
    bool InitRenderTargetD3D();
    bool InitShaders();
    bool InitScene();
    bool InitFactoryD2D();
    bool InitRenderTargetD2D();
    
    Microsoft::WRL::ComPtr<ID3D11Device> d3d_device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3d_device_context_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> d3d_render_target_view_;
    D3D11_VIEWPORT d3d_viewport_;
    
    Microsoft::WRL::ComPtr<IDXGISwapChain> dxgi_swap_chain_;

    Microsoft::WRL::ComPtr<ID2D1Factory> d2d_factory_;
    Microsoft::WRL::ComPtr<ID2D1RenderTarget> d2d_render_target_;

    VertexShader vertex_shader_2d_;
    VertexShader vertex_shader_primitive_;
    
    PixelShader pixel_shader_2d_;
    PixelShader pixel_shader_primitive_;
    
    ConstantBuffer<ConstantVertexBuffer2D> constant_buffer_2d_;
    ConstantBuffer<ConstantVertexPrimitiveBuffer> constant_primitive_buffer_;
    
    ConstantBuffer<ConstantPixelBuffer2D> constant_pixel_buffer_2d_;
    ConstantBuffer<ConstantPixelPrimitiveBuffer> constant_pixel_primitive_buffer_;

    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view_;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> depth_stencil_buffer_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
    
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_;
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;

    Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler_state_;

    Camera2D camera_2d_;

    std::unique_ptr<Texture> texture_;
    TempSprite sprite_;

    std::unique_ptr<SpriteBatch> sprite_batch_;

    Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer_;
    
};
