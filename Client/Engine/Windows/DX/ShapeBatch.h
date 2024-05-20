#pragma once
#include <vector>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Misc/EngineMacros.h"

class TexturePixelShader;
class TextureVertexShader;
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

    void DrawShapes(const SHARED_PTR<WindowsWindow>& kWindow, const std::vector<SHARED_PTR<Shape>>& kShapes);

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
    
    SHARED_PTR<DefaultVertexShader> vertex_shader_;
    SHARED_PTR<DefaultPixelShader> pixel_shader_;
    
};
