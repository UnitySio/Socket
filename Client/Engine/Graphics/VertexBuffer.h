#pragma once
#include <memory>

#include <d3d11.h>
#include <wrl/client.h>

template <typename T>
class VertexBuffer
{
public:
    VertexBuffer() : buffer_size_(0) {};
    virtual ~VertexBuffer() = default;

    HRESULT Init(ID3D11Device* device, const T* data, UINT num_vertices)
    {
        buffer_size_ = num_vertices;
        stride_ = std::make_unique<UINT>(sizeof(T));

        D3D11_BUFFER_DESC buffer_desc = {};
        ZeroMemory(&buffer_desc, sizeof(D3D11_BUFFER_DESC));
        
        buffer_desc.Usage = D3D11_USAGE_DEFAULT;
        buffer_desc.ByteWidth = sizeof(T) * num_vertices;
        buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        buffer_desc.CPUAccessFlags = 0;
        buffer_desc.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA buffer_data = {};
        ZeroMemory(&buffer_data, sizeof(buffer_data));
        
        buffer_data.pSysMem = data;

        const HRESULT hr = device->CreateBuffer(&buffer_desc, &buffer_data, buffer_.GetAddressOf());
        return hr;
    }

    inline ID3D11Buffer* Get() const { return buffer_.Get(); }
    inline ID3D11Buffer* const* GetAddressOf() const { return buffer_.GetAddressOf(); }
    inline UINT BufferSize() const { return buffer_size_; }
    inline UINT Stride() const { return *stride_; }
    inline UINT* StridePtr() const { return stride_.get(); }
    
private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer_;
    std::unique_ptr<UINT> stride_;
    UINT buffer_size_;
    
};
