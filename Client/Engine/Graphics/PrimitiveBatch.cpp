#include "PrimitiveBatch.h"
#include "DirectXTK/PrimitiveBatch.h"

PrimitiveBatch::PrimitiveBatch(ID3D11DeviceContext* device_context) :
    device_context_(device_context)
{
    Microsoft::WRL::ComPtr<ID3D11Device> device;
    device_context_->GetDevice(device.GetAddressOf());
    
    D3D11_BUFFER_DESC vertex_buffer_desc;
    ZeroMemory(&vertex_buffer_desc, sizeof(D3D11_BUFFER_DESC));

    vertex_buffer_desc.ByteWidth = sizeof(VertexPrimitive) * 2048;
    vertex_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertex_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    HRESULT hr = device->CreateBuffer(&vertex_buffer_desc, nullptr, vertex_buffer_.GetAddressOf());
    assert(SUCCEEDED(hr));

    D3D11_BUFFER_DESC index_buffer_desc;
    ZeroMemory(&index_buffer_desc, sizeof(D3D11_BUFFER_DESC));
    
    index_buffer_desc.ByteWidth = sizeof(UINT) * (2048 * 3);
    index_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    index_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    hr = device->CreateBuffer(&index_buffer_desc, nullptr, index_buffer_.GetAddressOf());
    assert(SUCCEEDED(hr));
    
    D3D11_INPUT_ELEMENT_DESC layout_primitive[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    constexpr UINT num_elements_primitive = ARRAYSIZE(layout_primitive);
    bool result = vertex_shader_.Init(device, L"..\\x64\\Debug\\VertexShaderPrimitive.cso", layout_primitive, num_elements_primitive);
    assert(SUCCEEDED(hr));
    
    result = pixel_shader_.Init(device, L"..\\x64\\Debug\\PixelShaderPrimitive.cso");
    assert(SUCCEEDED(hr));
    
    hr = constant_buffer_.Init(device.Get(), device_context_);
    assert(SUCCEEDED(hr));

    hr = constant_pixel_buffer_.Init(device.Get(), device_context_);
    assert(SUCCEEDED(hr));
}

void PrimitiveBatch::Begin(DirectX::XMMATRIX orthographic_matrix)
{
    device_context_->IASetInputLayout(vertex_shader_.GetInputLayout());
    device_context_->VSSetShader(vertex_shader_.GetShader(), nullptr, 0);
    device_context_->PSSetShader(pixel_shader_.GetShader(), nullptr, 0);

    DirectX::XMMATRIX wvp_matrix = DirectX::XMMatrixIdentity();
    device_context_->VSSetConstantBuffers(0, 1, constant_buffer_.GetAddressOf());
    constant_buffer_.data.mat = wvp_matrix * orthographic_matrix;
    constant_buffer_.ApplyChanges();

    device_context_->PSSetConstantBuffers(0, 1, constant_pixel_buffer_.GetAddressOf());
    constant_pixel_buffer_.ApplyChanges();
    
    constexpr UINT stride = sizeof(VertexPrimitive);
    constexpr UINT offset = 0;
    
    device_context_->IASetVertexBuffers(0, 1, vertex_buffer_.GetAddressOf(), &stride, &offset);
    device_context_->IASetIndexBuffer(index_buffer_.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void PrimitiveBatch::End()
{
}

void PrimitiveBatch::DrawLine(std::vector<VertexPrimitive>& vertices)
{
    LockBuffer(vertex_buffer_.Get(), &mapped_vertices_);

    CopyMemory(mapped_vertices_.pData, vertices.data(), sizeof(VertexPrimitive) * vertices.size());
    device_context_->Unmap(vertex_buffer_.Get(), 0);
    
    device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    device_context_->Draw(2, 0);
}

void PrimitiveBatch::DrawPolygon(std::vector<VertexPrimitive>& vertices)
{
    LockBuffer(vertex_buffer_.Get(), &mapped_vertices_);

    CopyMemory(mapped_vertices_.pData, vertices.data(), sizeof(VertexPrimitive) * vertices.size());
    device_context_->Unmap(vertex_buffer_.Get(), 0);
    
    device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    device_context_->Draw(vertices.size(), 0);
}

void PrimitiveBatch::DrawSolidPolygon(std::vector<VertexPrimitive>& vertices, std::vector<UINT>& indices)
{
    LockBuffer(vertex_buffer_.Get(), &mapped_vertices_);

    CopyMemory(mapped_vertices_.pData, vertices.data(), sizeof(VertexPrimitive) * vertices.size());
    device_context_->Unmap(vertex_buffer_.Get(), 0);

    LockBuffer(index_buffer_.Get(), &mapped_indices_);

    CopyMemory(mapped_indices_.pData, indices.data(), sizeof(UINT) * indices.size());
    device_context_->Unmap(index_buffer_.Get(), 0);
    
    device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    device_context_->DrawIndexed(indices.size(), 0, 0);
}

void PrimitiveBatch::LockBuffer(ID3D11Buffer* buffer, D3D11_MAPPED_SUBRESOURCE* mapped_resource)
{
    HRESULT hr = device_context_->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, mapped_resource);
    assert(SUCCEEDED(hr));
}
