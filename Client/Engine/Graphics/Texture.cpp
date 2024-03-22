#include "Texture.h"

#include <vector>

#include "DirectXTK/WICTextureLoader.h"

Texture::Texture() :
    width_(0),
    height_(0)
{
}

bool Texture::Load(ID3D11Device* device, const std::wstring& kPath)
{
    HRESULT hr = DirectX::CreateWICTextureFromFile(device, kPath.c_str(), texture_.GetAddressOf(),
                                                   texture_view_.GetAddressOf());
    if (FAILED(hr)) return false;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> tex_2d;
    texture_->QueryInterface<ID3D11Texture2D>(tex_2d.GetAddressOf());
    if (!tex_2d) return false;

    D3D11_TEXTURE2D_DESC tex_2d_desc;
    tex_2d->GetDesc(&tex_2d_desc);

    width_ = tex_2d_desc.Width;
    height_ = tex_2d_desc.Height;
    
    std::vector<Vertex2D> vertices =
    {
        {-.5f, -.5f, 0.f, 0.f, 1.f}, // 왼쪽 아래
        {.5f, -.5f, 0.f, 1.f, 1.f}, // 오른쪽 아래
        {-.5f, .5f, 0.f, 0.f, 0.f}, // 왼쪽 위
        {.5f, .5f, 0.f, 1.f, 0.f} // 오른쪽 위
    };

    std::vector<DWORD> indices =
    {
        0, 1, 2,
        2, 1, 3
    };
    
    hr = vertices_.Init(device, vertices.data(), vertices.size());
    if (FAILED(hr)) return false;

    hr = indices_.Init(device, indices.data(), indices.size());
    if (FAILED(hr)) return false;

    return true;
}
    