#pragma once
#include <wrl/client.h>

#include "DirectXTK/CommonStates.h"

struct ID3D11RasterizerState;
struct ID3D11BlendState;
struct ID3D11SamplerState;

class RenderingPolicy
{
public:
    RenderingPolicy();
    ~RenderingPolicy();

    bool InitResources();

private:
    Microsoft::WRL::ComPtr<ID3D11SamplerState> point_sampler_state_wrap_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> bilinear_sampler_state_wrap_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> bilinear_sampler_state_clamp_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> point_sampler_state_clamp_;
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
    
};
