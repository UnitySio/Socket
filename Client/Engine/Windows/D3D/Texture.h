#pragma once
#include <d3d11.h>
#include <string>
#include <wrl/client.h>

#include "Shape.h"
#include "Math/MathTypes.h"

class Texture : public Shape
{
public:
    Texture();
    ~Texture() = default;
    
    bool Load(const std::wstring& kFileName);

    MathTypes::uint32 GetWidth() const { return width_; }
    MathTypes::uint32 GetHeight() const { return height_; }

private:
    Microsoft::WRL::ComPtr<ID3D11Resource> resource_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> resource_view_;

    MathTypes::uint32 width_;
    MathTypes::uint32 height_;
    
};
