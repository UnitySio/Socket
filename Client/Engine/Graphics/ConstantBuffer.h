#pragma once
#include <d3d11.h>
#include <wrl/client.h>

template <typename T>
class ConstantBuffer
{
public:
    ConstantBuffer() = default;
    virtual ~ConstantBuffer() = default;

    T data;

    HRESULT Init(ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        context_ = device_context;

        D3D11_BUFFER_DESC buffer_desc = {};
        ZeroMemory(&buffer_desc, sizeof(D3D11_BUFFER_DESC));

        buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
        buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        buffer_desc.MiscFlags = 0;
        buffer_desc.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)));
        buffer_desc.StructureByteStride = 0;

        HRESULT hr = device->CreateBuffer(&buffer_desc, 0, buffer_.GetAddressOf());
        return hr;
    }

    bool ApplyChanges()
    {
        D3D11_MAPPED_SUBRESOURCE mapped_resource;
        HRESULT hr = context_->Map(buffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);
        if (FAILED(hr)) return false;

        CopyMemory(mapped_resource.pData, &data, sizeof(T));
        context_->Unmap(buffer_.Get(), 0);
        return true;
    }

    inline ID3D11Buffer* Get() const { return buffer_.Get(); }
    ID3D11Buffer* const* GetAddressOf() const { return buffer_.GetAddressOf(); }

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer_;
    ID3D11DeviceContext* context_;
    
};
