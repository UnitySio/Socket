#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include <string>

#include "IndexBuffer.h"
#include "Vertex.h"
#include "VertexBuffer.h"

class Texture
{
public:
    Texture();
    ~Texture() = default;

    bool Load(ID3D11Device* device, const std::wstring& path);
    
    inline const UINT& GetWidth() const { return width_; }
    inline const UINT& GetHeight() const { return height_; }

private:
    friend class Sprite;
    
    Microsoft::WRL::ComPtr<ID3D11Resource> texture_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture_view_;

    UINT width_;
    UINT height_;

    IndexBuffer indices_;
    VertexBuffer<Vertex2D> vertices_;
    
};
