#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#include "../Singleton.h"

#include <d3d11.h>
#include <d2d1.h>
#include <dwrite.h>

#include "box2d/b2_draw.h"

struct b2Vec2;

class Graphics : public Singleton<Graphics>
{
public:
    Graphics();
    virtual ~Graphics() override;

    bool Init();
    
    void BeginRenderD3D();
    void EndRenderD3D();

    void DrawLine(b2Vec2 start, b2Vec2 end, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawBox(b2Vec2 center, b2Vec2 size, float angle, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawSolidBox(b2Vec2 center, b2Vec2 size, float angle, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawCircle(b2Vec2 center, float radius, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawSolidCircle(b2Vec2 center, float radius, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawPolygon(const b2Vec2* kVertices, int32 vertex_count, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawSolidPolygon(const b2Vec2* kVertices, int32 vertex_count, b2Color color = b2Color(1.f, 1.f, 1.f));
    void DrawTexture(ID2D1Bitmap* texture, b2Vec2 center, b2Vec2 scale = b2Vec2(1.f, 1.f), float angle = 0.f, float opacity = 1.f);

    ID2D1Bitmap* LoadTexture(const WCHAR* kFileName);

    inline ID3D11Device* GetD3DDevice() const { return d3d_device_; }
    inline ID3D11DeviceContext* GetD3DDeviceContext() const { return d3d_device_context_; }
    inline void BeginRenderD2D() const { d2d_render_target_->BeginDraw(); }
    inline void EndRenderD2D() const { d2d_render_target_->EndDraw(); }

private:
    bool InitDeviceD3D();
    bool InitRenderTargetD3D();
    bool InitFactoryD2D();
    bool InitRenderTargetD2D();
    
    ID3D11Device* d3d_device_;
    ID3D11DeviceContext* d3d_device_context_;
    ID3D11RenderTargetView* d3d_render_target_view_;
    D3D11_VIEWPORT d3d_viewport_;
    
    IDXGISwapChain* dxgi_swap_chain_;

    ID2D1Factory* d2d_factory_;
    ID2D1RenderTarget* d2d_render_target_;
    
};
