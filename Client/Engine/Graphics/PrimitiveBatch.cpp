#include "PrimitiveBatch.h"

PrimitiveBatch::PrimitiveBatch(ID3D11DeviceContext* device_context) :
    device_context_(device_context)
{
    Microsoft::WRL::ComPtr<ID3D11Device> device;
    device_context_->GetDevice(device.GetAddressOf());
    
    D3D11_BUFFER_DESC vertex_buffer_desc;
    ZeroMemory(&vertex_buffer_desc, sizeof(D3D11_BUFFER_DESC));

    vertex_buffer_desc.ByteWidth = sizeof(VertexPrimitive) * 2;
    vertex_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertex_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    HRESULT hr = device->CreateBuffer(&vertex_buffer_desc, nullptr, vertex_buffer_.GetAddressOf());
    assert(SUCCEEDED(hr));
    
    D3D11_INPUT_ELEMENT_DESC layout_primitive[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    constexpr UINT num_elements_primitive = ARRAYSIZE(layout_primitive);
    bool result = vertex_shader_primitive_.Init(device, L"..\\x64\\Debug\\VertexShaderPrimitive.cso", layout_primitive, num_elements_primitive);
    assert(SUCCEEDED(hr));
    
    result = pixel_shader_primitive_.Init(device, L"..\\x64\\Debug\\PixelShaderPrimitive.cso");
    assert(SUCCEEDED(hr));
    
    hr = constant_primitive_buffer_.Init(device.Get(), device_context_);
    assert(SUCCEEDED(hr));

    hr = constant_pixel_primitive_buffer_.Init(device.Get(), device_context_);
    assert(SUCCEEDED(hr));
}

void PrimitiveBatch::Begin(DirectX::XMMATRIX orthographic_matrix)
{
    device_context_->IASetInputLayout(vertex_shader_primitive_.GetInputLayout());
    device_context_->VSSetShader(vertex_shader_primitive_.GetShader(), nullptr, 0);
    device_context_->PSSetShader(pixel_shader_primitive_.GetShader(), nullptr, 0);

    DirectX::XMMATRIX wvp_matrix = DirectX::XMMatrixIdentity();
    device_context_->VSSetConstantBuffers(0, 1, constant_primitive_buffer_.GetAddressOf());
    constant_primitive_buffer_.data.mat = wvp_matrix * orthographic_matrix;
    constant_primitive_buffer_.ApplyChanges();

    device_context_->PSSetConstantBuffers(0, 1, constant_pixel_primitive_buffer_.GetAddressOf());
    constant_pixel_primitive_buffer_.ApplyChanges();
    
    constexpr UINT stride = sizeof(VertexPrimitive);
    constexpr UINT offset = 0;
    
    device_context_->IASetVertexBuffers(0, 1, vertex_buffer_.GetAddressOf(), &stride, &offset);
}

void PrimitiveBatch::End()
{
}

void PrimitiveBatch::DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a)
{
    std::vector<VertexPrimitive> vertices = {
        VertexPrimitive(x1, y1, 0.f, r, g, b, a),
        VertexPrimitive(x2, y2, 0.f, r, g, b, a)
    };

    LockBuffer(vertices);
    
    device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    device_context_->Draw(2, 0);
}

void PrimitiveBatch::LockBuffer(std::vector<VertexPrimitive>& vertices)
{
    D3D11_MAPPED_SUBRESOURCE mapped_vertices;
    HRESULT hr = device_context_->Map(vertex_buffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_vertices);
    assert(SUCCEEDED(hr));

    CopyMemory(mapped_vertices.pData, vertices.data(), sizeof(VertexPrimitive) * vertices.size());

    device_context_->Unmap(vertex_buffer_.Get(), 0);
}
