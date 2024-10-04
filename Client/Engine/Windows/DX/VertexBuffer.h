#pragma once
#include "Renderer.h"

#include <d3d11.h>
#include <wrl/client.h>

#include "Math/MathTypes.h"

class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    bool CreateBuffer(MathTypes::uint32 stride, bool cpu_access = false, bool gpu_access = true);

    void* Lock();
    
    void Unlock();

    inline MathTypes::uint32 GetBufferSize() const { return buffer_size_; }
    
    inline ID3D11Buffer* GetResource() const { return buffer_.Get(); }

private:
    MathTypes::uint32 stride_;
    MathTypes::uint32 buffer_size_;

    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer_;
    
};
