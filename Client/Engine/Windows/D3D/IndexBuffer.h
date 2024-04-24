#pragma once
#include <d3d11.h>
#include <wrl/client.h>

#include "Math/MathTypes.h"

class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();

    bool CreateBuffer();

    void* Lock();

    void Unlock();
    
    inline ID3D11Buffer* GetResource() const { return buffer_.Get(); }

private:
    MathTypes::uint32 indices_;
    
    Microsoft::WRL::ComPtr<ID3D11Buffer> buffer_;
    
};
