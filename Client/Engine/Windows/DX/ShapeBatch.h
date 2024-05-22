#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <vector>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Misc/EngineMacros.h"

class WindowsWindow;
class Shape;
class DefaultVertexShader;
class DefaultPixelShader;

class ShapeBatch
{
public:
    ShapeBatch();
    ~ShapeBatch() = default;

    bool Init();

    void DrawShapes(const SHARED_PTR<WindowsWindow>& kWindow, const std::vector<SHARED_PTR<Shape>>& kShapes);

private:
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
    
    VertexBuffer vertex_buffer_;
    IndexBuffer index_buffer_;
    
    SHARED_PTR<DefaultVertexShader> vertex_shader_;
    SHARED_PTR<DefaultPixelShader> pixel_shader_;
    
};
