#pragma once
#include <DirectXMath.h>
#include <string>

#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"

class ID3D11DeviceContext;

class SpriteBatch
{
public:
    SpriteBatch(ID3D11DeviceContext* device_context);
    ~SpriteBatch() = default;

    void Begin(DirectX::XMMATRIX orthographic_matrix);
    void End();
    void Draw(class Sprite* sprite, const std::wstring& kName, float x = 0.f, float y = 0.f);

private:
    ID3D11DeviceContext* device_context_;

    DirectX::XMMATRIX orthographic_matrix_;

    ConstantBuffer<ConstantVertexBuffer2D> constant_buffer_;
    ConstantBuffer<ConstantPixelBuffer2D> constant_pixel_buffer_;
    
};
