#pragma once
#include <DirectXMath.h>
#include <string>

#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"
#include "Windows/D3D/Shaders.h"
#include "Math/Vector2.h"

class ID3D11DeviceContext;

class SpriteBatch
{
public:
    SpriteBatch(ID3D11DeviceContext* device_context);
    ~SpriteBatch() = default;

    void Begin(DirectX::XMMATRIX orthographic_matrix);
    void End();
    void Draw(class Sprite* sprite, const std::wstring& kName, Math::Vector2 location = {0.f, 0.f}, Math::Vector2 scale = {1.f, 1.f}, float angle = 0.f);

private:
    ID3D11DeviceContext* device_context_;

    DirectX::XMMATRIX orthographic_matrix_;
    
    VertexShader vertex_shader_;
    
    PixelShader pixel_shader_;

    ConstantBuffer<ConstantVertexBuffer2D> constant_buffer_;
    ConstantBuffer<ConstantPixelBuffer2D> constant_pixel_buffer_;
    
};
