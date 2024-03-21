#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <wrl/client.h>

#include "Shaders.h"
#include "Vertex.h"
#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"

class PrimitiveBatch
{
public:
    PrimitiveBatch(ID3D11DeviceContext* device_context);
    ~PrimitiveBatch() = default;
    
    void Begin(DirectX::XMMATRIX orthographic_matrix);
    void End();
    void DrawLine(std::vector<VertexPrimitive>& vertices);
    void DrawPolygon(std::vector<VertexPrimitive>& vertices);
    void DrawSolidPolygon(std::vector<VertexPrimitive>& vertices, std::vector<UINT>& indices);

private:
    void LockBuffer(ID3D11Buffer* buffer, D3D11_MAPPED_SUBRESOURCE* mapped_resource);
    
    ID3D11DeviceContext* device_context_;

    D3D11_MAPPED_SUBRESOURCE mapped_vertices_;
    D3D11_MAPPED_SUBRESOURCE mapped_indices_;
    
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer_;
    Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer_;
    
    VertexShader vertex_shader_primitive_;
    
    PixelShader pixel_shader_primitive_;
    
    ConstantBuffer<ConstantVertexPrimitiveBuffer> constant_primitive_buffer_;
    
    ConstantBuffer<ConstantPixelPrimitiveBuffer> constant_pixel_primitive_buffer_;
    
};
