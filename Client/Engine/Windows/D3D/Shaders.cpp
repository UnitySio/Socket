#include "Shaders.h"

#include <d3dcompiler.h>

#include "Misc/EngineMacros.h"
#include "Windows/D3D/Renderer.h"

VertexShader::VertexShader() :
    shader_(nullptr),
    shader_buffer_(nullptr),
    input_layout_(nullptr)
{
}

bool VertexShader::Create(const std::wstring& path, const D3D11_INPUT_ELEMENT_DESC* layout, UINT layout_count)
{
    HRESULT hr = D3DReadFileToBlob(path.c_str(), shader_buffer_.GetAddressOf());
    if (FAILED(hr)) return false;

    hr = g_d3d_device->CreateVertexShader(shader_buffer_->GetBufferPointer(), shader_buffer_->GetBufferSize(), nullptr,
                                          shader_.GetAddressOf());
    if (FAILED(hr)) return false;

    hr = g_d3d_device->CreateInputLayout(layout, layout_count, shader_buffer_->GetBufferPointer(),
                                         shader_buffer_->GetBufferSize(), input_layout_.GetAddressOf());
    if (FAILED(hr)) return false;

    return true;
}

void VertexShader::BindShader()
{
    g_d3d_device_context->IASetInputLayout(input_layout_.Get());
    g_d3d_device_context->VSSetShader(shader_.Get(), nullptr, 0);
}

void VertexShader::BindParameters()
{
    UpdateParameters();
}

PixelShader::PixelShader() :
    shader_(nullptr),
    shader_buffer_(nullptr)
{
}

bool PixelShader::Create(const std::wstring& path)
{
    HRESULT hr = D3DReadFileToBlob(path.c_str(), shader_buffer_.GetAddressOf());
    if (FAILED(hr)) return false;

    hr = g_d3d_device->CreatePixelShader(shader_buffer_->GetBufferPointer(), shader_buffer_->GetBufferSize(), nullptr,
                                         shader_.GetAddressOf());
    if (FAILED(hr)) return false;

    return true;
}

void PixelShader::BindShader()
{
    g_d3d_device_context->PSSetShader(shader_.Get(), nullptr, 0);
}

void PixelShader::BindParameters()
{
    UpdateParameters();
}

DefaultVertexShader::DefaultVertexShader()
{
    CHECK(constant_buffer_.Create());

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    bool r = Create(L"..\\x64\\Debug\\DefaultVertexShader.cso", layout, ARRAYSIZE(layout));
    CHECK(r);
}

void DefaultVertexShader::SetWorldMatrix(const DirectX::XMMATRIX& mat)
{
    constant_buffer_.GetBufferData().mat = mat;
}

void DefaultVertexShader::SetUVOffset(const DirectX::XMFLOAT2& offset)
{
    constant_buffer_.GetBufferData().uv_offset = offset;
}

void DefaultVertexShader::SetUVScale(const DirectX::XMFLOAT2& scale)
{
    constant_buffer_.GetBufferData().uv_scale = scale;
}

void DefaultVertexShader::UpdateParameters()
{
    VertexShader::UpdateParameters();

    g_d3d_device_context->VSSetConstantBuffers(0, 1, constant_buffer_.GetResourceAddress());
    constant_buffer_.UpdateBuffer();
}

DefaultPixelShader::DefaultPixelShader()
{
    CHECK(constant_buffer_.Create());

    bool r = Create(L"..\\x64\\Debug\\DefaultPixelShader.cso");
    CHECK(r);
}

void DefaultPixelShader::UpdateParameters()
{
    PixelShader::UpdateParameters();

    g_d3d_device_context->PSSetConstantBuffers(0, 1, constant_buffer_.GetResourceAddress());
    constant_buffer_.UpdateBuffer();
}
