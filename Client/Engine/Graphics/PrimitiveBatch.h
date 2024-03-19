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
    void DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a);

private:
    void LockBuffer(std::vector<VertexPrimitive>& vertices);
    
    ID3D11DeviceContext* device_context_;
    
    Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer_;
    
    VertexShader vertex_shader_primitive_;
    
    PixelShader pixel_shader_primitive_;
    
    ConstantBuffer<ConstantVertexPrimitiveBuffer> constant_primitive_buffer_;
    
    ConstantBuffer<ConstantPixelPrimitiveBuffer> constant_pixel_primitive_buffer_;
    
};
