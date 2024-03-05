#include "Shaders.h"

#include <d3dcompiler.h>

VertexShader::VertexShader() :
    shader_(nullptr),
    shader_buffer_(nullptr)
{
}

bool VertexShader::Init(Microsoft::WRL::ComPtr<ID3D11Device>& device, const std::wstring& path, const D3D11_INPUT_ELEMENT_DESC* layout, UINT num_elements)
{
    HRESULT result = D3DReadFileToBlob(path.c_str(), shader_buffer_.GetAddressOf());
    if (FAILED(result)) return false;

    result = device->CreateVertexShader(shader_buffer_->GetBufferPointer(), shader_buffer_->GetBufferSize(), nullptr, shader_.GetAddressOf());
    if (FAILED(result)) return false;

    result = device->CreateInputLayout(layout, num_elements, shader_buffer_->GetBufferPointer(), shader_buffer_->GetBufferSize(), input_layout_.GetAddressOf());
    if (FAILED(result)) return false;

    return true;
}

PixelShader::PixelShader() :
    shader_(nullptr),
    shader_buffer_(nullptr)
{
}

bool PixelShader::Init(Microsoft::WRL::ComPtr<ID3D11Device>& device, const std::wstring& path)
{
    HRESULT result = D3DReadFileToBlob(path.c_str(), shader_buffer_.GetAddressOf());
    if (FAILED(result)) return false;

    result = device->CreatePixelShader(shader_buffer_->GetBufferPointer(), shader_buffer_->GetBufferSize(), nullptr, shader_.GetAddressOf());
    if (FAILED(result)) return false;

    return true;
}
