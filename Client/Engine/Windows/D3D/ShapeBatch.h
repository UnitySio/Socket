#pragma once
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
    ~ShapeBatch();

    bool Init();

    void DrawShapes(const SharedPtr<WindowsWindow>& kWindow, const std::vector<SharedPtr<Shape>>& kShapes);

private:
    Microsoft::WRL::ComPtr<ID3D11SamplerState> point_sampler_state_wrap_;
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
    
    VertexBuffer vertex_buffer_;
    IndexBuffer index_buffer_;
    
    SharedPtr<DefaultVertexShader> vertex_shader_;
    SharedPtr<DefaultPixelShader> pixel_shader_;
    
};
