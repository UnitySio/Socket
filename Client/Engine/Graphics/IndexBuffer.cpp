#include "IndexBuffer.h"

IndexBuffer::IndexBuffer() : buffer_size_(0)
{
}

HRESULT IndexBuffer::Init(ID3D11Device* device, DWORD* data, UINT num_indices)
{
    if (buffer_.Get()) buffer_.Reset();
    
    buffer_size_ = num_indices;

    D3D11_BUFFER_DESC buffer = {};
    ZeroMemory(&buffer, sizeof(D3D11_BUFFER_DESC));
    
    buffer.Usage = D3D11_USAGE_DEFAULT;
    buffer.ByteWidth = sizeof(DWORD) * num_indices;
    buffer.BindFlags = D3D11_BIND_INDEX_BUFFER;
    buffer.CPUAccessFlags = 0;
    buffer.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA buffer_data = {};
    ZeroMemory(&buffer_data, sizeof(D3D11_SUBRESOURCE_DATA));
    
    buffer_data.pSysMem = data;

    return device->CreateBuffer(&buffer, &buffer_data, buffer_.GetAddressOf());
}
