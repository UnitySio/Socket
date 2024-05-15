#include "IndexBuffer.h"

#include "Renderer.h"

IndexBuffer::IndexBuffer() :
    indices_(0),
    buffer_(nullptr)
{
}

IndexBuffer::~IndexBuffer()
{
}

bool IndexBuffer::CreateBuffer()
{
    indices_ = 2048 * 3;
    MathTypes::uint32 buffer_size = indices_ * sizeof(MathTypes::uint32);

    D3D11_BUFFER_DESC buffer_desc;
    ZeroMemory(&buffer_desc, sizeof(D3D11_BUFFER_DESC));

    buffer_desc.ByteWidth = buffer_size;
    buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
    buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    buffer_desc.MiscFlags = 0;

    HRESULT hr = Renderer::Get()->GetDevice()->CreateBuffer(&buffer_desc, nullptr, buffer_.GetAddressOf());
    return SUCCEEDED(hr);
}

void* IndexBuffer::Lock()
{
    D3D11_MAPPED_SUBRESOURCE mapped_resource;
    Renderer::Get()->GetDeviceContext()->Map(buffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
    return mapped_resource.pData;
}

void IndexBuffer::Unlock()
{
    Renderer::Get()->GetDeviceContext()->Unmap(buffer_.Get(), 0);
}
