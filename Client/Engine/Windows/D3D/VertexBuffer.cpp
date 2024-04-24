#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer() :
    stride_(0),
    buffer_size_(0),
    buffer_(nullptr)
{
}

VertexBuffer::~VertexBuffer()
{
}

bool VertexBuffer::CreateBuffer(MathTypes::uint32 stride)
{
    stride_ = stride;
    buffer_size_ = stride * 2048;

    D3D11_BUFFER_DESC buffer_desc;
    ZeroMemory(&buffer_desc, sizeof(D3D11_BUFFER_DESC));

    buffer_desc.ByteWidth = buffer_size_;
    buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    buffer_desc.MiscFlags = 0;

    HRESULT hr = g_d3d_device->CreateBuffer(&buffer_desc, nullptr, buffer_.GetAddressOf());
    return SUCCEEDED(hr);
}

void* VertexBuffer::Lock()
{
    D3D11_MAPPED_SUBRESOURCE mapped_resource;
    g_d3d_device_context->Map(buffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
    return mapped_resource.pData;
}

void VertexBuffer::Unlock()
{
    g_d3d_device_context->Unmap(buffer_.Get(), 0);
}
