#include "Shaders.h"

#include <d3dcompiler.h>

#include "Misc/EngineMacros.h"
#include "Windows/D3D/Renderer.h"

VertexShader::VertexShader() :
    shader_(nullptr),
    shader_buffer_(nullptr),
    input_layout_(nullptr)
{
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    
    bool r = Create(L".\\Game_Data\\VertexShader2D.cso", layout, ARRAYSIZE(layout));
    CHECK(r);
}

bool VertexShader::Create(const std::wstring& path, const D3D11_INPUT_ELEMENT_DESC* layout, UINT layout_count)
{
    HRESULT hr = D3DReadFileToBlob(path.c_str(), shader_buffer_.GetAddressOf());
    if (FAILED(hr)) return false;

    hr = g_d3d_device->CreateVertexShader(shader_buffer_->GetBufferPointer(), shader_buffer_->GetBufferSize(), nullptr, shader_.GetAddressOf());
    if (FAILED(hr)) return false;

    hr = g_d3d_device->CreateInputLayout(layout, layout_count, shader_buffer_->GetBufferPointer(), shader_buffer_->GetBufferSize(), input_layout_.GetAddressOf());
    if (FAILED(hr)) return false;

    return true;
}

void VertexShader::BindShader()
{
    g_d3d_device_context->IASetInputLayout(input_layout_.Get());
    g_d3d_device_context->VSSetShader(shader_.Get(), nullptr, 0);
}

PixelShader::PixelShader() :
    shader_(nullptr),
    shader_buffer_(nullptr)
{
    bool r = Create(L".\\Game_Data\\PixelShader2D.cso");
    CHECK(r);
}

bool PixelShader::Create(const std::wstring& path)
{
    HRESULT hr = D3DReadFileToBlob(path.c_str(), shader_buffer_.GetAddressOf());
    if (FAILED(hr)) return false;

    hr = g_d3d_device->CreatePixelShader(shader_buffer_->GetBufferPointer(), shader_buffer_->GetBufferSize(), nullptr, shader_.GetAddressOf());
    if (FAILED(hr)) return false;

    return true;
}

void PixelShader::BindShader()
{
    g_d3d_device_context->PSSetShader(shader_.Get(), nullptr, 0);
}
