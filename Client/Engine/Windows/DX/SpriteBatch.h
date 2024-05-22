#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <vector>

#include "Misc/EngineMacros.h"

class Sprite;
class WindowsWindow;

class SpriteBatch
{
public:
    SpriteBatch();
    ~SpriteBatch() = default;

    bool Init();
    
    void DrawSprites(const SHARED_PTR<WindowsWindow>& kWindow, const std::vector<SHARED_PTR<Sprite>>& kSprites);

private:
    Microsoft::WRL::ComPtr<ID3D11SamplerState> point_sampler_state_wrap_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> bilinear_sampler_state_wrap_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> bilinear_sampler_state_clamp_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> point_sampler_state_clamp_;
    
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
    
};
