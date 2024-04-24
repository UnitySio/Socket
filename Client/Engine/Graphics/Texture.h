#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <string>

#include "IndexBuffer_Temp.h"
#include "Vertex.h"
#include "VertexBuffer.h"

class Texture
{
public:
    Texture();
    virtual ~Texture() = default;

    virtual bool Load(ID3D11Device* device, const std::wstring& kPath);
    
    inline const UINT& GetWidth() const { return width_; }
    inline const UINT& GetHeight() const { return height_; }

protected:
    friend class SpriteBatch;
    
    Microsoft::WRL::ComPtr<ID3D11Resource> texture_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture_view_;

    UINT width_;
    UINT height_;

    IndexBuffer_Temp indices_;
    VertexBuffer<Vertex2D> vertices_;
    
};
