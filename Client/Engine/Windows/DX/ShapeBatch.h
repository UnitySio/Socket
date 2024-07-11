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

    void DrawShapes(const std::shared_ptr<WindowsWindow>& kWindow, const std::vector<std::shared_ptr<Shape>>& kShapes);

private:
    Microsoft::WRL::ComPtr<ID3D11SamplerState> point_sampler_state_wrap_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> bilinear_sampler_state_wrap_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> bilinear_sampler_state_clamp_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> point_sampler_state_clamp_;
    
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
    
    VertexBuffer vertex_buffer_;
    IndexBuffer index_buffer_;
    
    std::shared_ptr<DefaultVertexShader> vertex_shader_;
    std::shared_ptr<DefaultPixelShader> pixel_shader_;
    
};
