#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <string>

class Texture
{
public:
    Texture();
    ~Texture() = default;

    bool Load(ID3D11Device* device, const std::wstring& path);

    inline ID3D11ShaderResourceView* Get() const { return texture_view_.Get(); }
    inline ID3D11ShaderResourceView* const* GetAddress() const { return texture_view_.GetAddressOf(); }
    
    inline const UINT& GetWidth() const { return width_; }
    inline const UINT& GetHeight() const { return height_; }

private:
    Microsoft::WRL::ComPtr<ID3D11Resource> texture_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture_view_;

    UINT width_;
    UINT height_;
    
};
