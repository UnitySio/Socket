#include "Texture.h"

#include "DirectXTK/WICTextureLoader.h"

bool Texture::Load(ID3D11Device* device, const std::wstring& path)
{
    HRESULT hr = DirectX::CreateWICTextureFromFile(device, path.c_str(), texture_.GetAddressOf(),
                                                   texture_view_.GetAddressOf());
    if (FAILED(hr)) return false;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> tex_2d;
    texture_->QueryInterface<ID3D11Texture2D>(tex_2d.GetAddressOf());
    if (!tex_2d) return false;

    D3D11_TEXTURE2D_DESC tex_2d_desc;
    tex_2d->GetDesc(&tex_2d_desc);

    width_ = tex_2d_desc.Width;
    height_ = tex_2d_desc.Height;

    return true;
}
    