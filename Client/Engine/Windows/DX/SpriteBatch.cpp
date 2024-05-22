﻿#include "SpriteBatch.h"

#include "Renderer.h"

SpriteBatch::SpriteBatch()
{
}

bool SpriteBatch::Init()
{
    D3D11_SAMPLER_DESC sampler_desc;
    ZeroMemory(&sampler_desc, sizeof(D3D11_SAMPLER_DESC));

    sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampler_desc.MinLOD = 0;
    sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

    HRESULT hr = Renderer::Get()->GetDevice()->CreateSamplerState(&sampler_desc, point_sampler_state_wrap_.GetAddressOf());
    if (FAILED(hr)) return false;

    sampler_desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
    hr = Renderer::Get()->GetDevice()->CreateSamplerState(&sampler_desc, bilinear_sampler_state_wrap_.GetAddressOf());
    if (FAILED(hr)) return false;

    sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

    hr = Renderer::Get()->GetDevice()->CreateSamplerState(&sampler_desc, bilinear_sampler_state_clamp_.GetAddressOf());
    if (FAILED(hr)) return false;

    sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    hr = Renderer::Get()->GetDevice()->CreateSamplerState(&sampler_desc, point_sampler_state_clamp_.GetAddressOf());
    if (FAILED(hr)) return false;
    
    D3D11_BLEND_DESC blend_desc;
    ZeroMemory(&blend_desc, sizeof(D3D11_BLEND_DESC));

    D3D11_RENDER_TARGET_BLEND_DESC render_target_blend_desc;
    ZeroMemory(&render_target_blend_desc, sizeof(D3D11_RENDER_TARGET_BLEND_DESC));

    render_target_blend_desc.BlendEnable = true;
    render_target_blend_desc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    render_target_blend_desc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    render_target_blend_desc.BlendOp = D3D11_BLEND_OP_ADD;
    render_target_blend_desc.SrcBlendAlpha = D3D11_BLEND_ONE;
    render_target_blend_desc.DestBlendAlpha = D3D11_BLEND_ZERO;
    render_target_blend_desc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    render_target_blend_desc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    blend_desc.RenderTarget[0] = render_target_blend_desc;

    hr = Renderer::Get()->GetDevice()->CreateBlendState(&blend_desc, blend_state_.GetAddressOf());
    if (FAILED(hr)) return false;

    D3D11_RASTERIZER_DESC rasterizer_desc;
    ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));

    rasterizer_desc.FillMode = D3D11_FILL_SOLID;
    rasterizer_desc.CullMode = D3D11_CULL_NONE;

    hr = Renderer::Get()->GetDevice()->CreateRasterizerState(&rasterizer_desc, rasterizer_state_.GetAddressOf());
    if (FAILED(hr)) return false;

    D3D11_DEPTH_STENCIL_DESC depth_stencil_state_desc;
    ZeroMemory(&depth_stencil_state_desc, sizeof(D3D11_DEPTH_STENCIL_DESC));

    depth_stencil_state_desc.DepthEnable = true;
    depth_stencil_state_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depth_stencil_state_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

    hr = Renderer::Get()->GetDevice()->CreateDepthStencilState(&depth_stencil_state_desc, depth_stencil_state_.GetAddressOf());
    return SUCCEEDED(hr);
}

void SpriteBatch::DrawSprites(const std::shared_ptr<WindowsWindow>& kWindow, const std::vector<std::shared_ptr<Sprite>>& kSprites)
{
    Viewport* viewport = Renderer::Get()->FindViewport(kWindow.get());
    CHECK(viewport);

    for (auto& sprite : kSprites)
    {
    }
}
