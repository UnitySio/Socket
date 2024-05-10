#include "Texture.h"

#include "Renderer.h"
#include "DirectXTK/WICTextureLoader.h"

Texture::Texture() :
    resource_(nullptr),
    resource_view_(nullptr),
    width_(0),
    height_(0)
{
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
