﻿#include "Texture.h"

#include "Renderer.h"
#include "DirectXTK/WICTextureLoader.h"

Texture::Texture() :
    width_(0),
    height_(0),
    uv_offset_(Math::Vector2::Zero()),
    uv_scale_(Math::Vector2::One()),
    resource_(nullptr),
    resource_view_(nullptr),
    vertices_(),
    indices_(),
    wrap_mode_(WrapMode::kReapet),
    filter_mode_(FilterMode::kPoint)
{
    vertices_ = {
        {{0.f, 0.f, 0.f}, {}, {0.f, 1.f}},
        {{1.f, 0.f, 0.f}, {}, {1.f, 1.f}},
        {{0.f, 1.f, 0.f}, {}, {0.f, 0.f}},
        {{1.f, 1.f, 0.f}, {}, {1.f, 0.f}}
    };

    indices_ = {
        0, 1, 2,
        2, 1, 3
    };
}

bool Texture::Load(const std::wstring& kFileName)
{
    HRESULT hr = DirectX::CreateWICTextureFromFile(
        g_d3d_device.Get(),
        kFileName.c_str(),
        resource_.GetAddressOf(),
        resource_view_.GetAddressOf()
    );

    if (FAILED(hr)) return false;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
    hr = resource_->QueryInterface<ID3D11Texture2D>(texture.GetAddressOf());
    if (FAILED(hr)) return false;

    D3D11_TEXTURE2D_DESC texture_desc;
    texture->GetDesc(&texture_desc);

    width_ = texture_desc.Width;
    height_ = texture_desc.Height;
}