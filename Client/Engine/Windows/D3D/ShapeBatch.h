#pragma once
#include <memory>
#include <vector>

#include "IndexBuffer.h"
#include "VertexBuffer.h"

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

    void DrawShape(const std::shared_ptr<WindowsWindow>& kWindow, std::shared_ptr<Shape>& shape);

private:
    Microsoft::WRL::ComPtr<ID3D11SamplerState> point_sampler_state_wrap_;
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
    
    VertexBuffer vertex_buffer_;
    IndexBuffer index_buffer_;
    
    std::shared_ptr<DefaultVertexShader> vertex_shader_;
    std::shared_ptr<DefaultPixelShader> pixel_shader_;
    
};
