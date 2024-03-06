#pragma once
#include <d3d11.h>
#include <wrl/client.h>

class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer() = default;

    HRESULT Init(ID3D11Device* device, DWORD* data, UINT num_indices);

    inline ID3D11Buffer* Get() const { return buffer_.Get(); }
    inline ID3D11Buffer* const* GetAddressOf() const { return buffer_.GetAddressOf(); }
    inline UINT BufferSize() const { return buffer_size_; }

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer_;
    UINT buffer_size_;
    
};
