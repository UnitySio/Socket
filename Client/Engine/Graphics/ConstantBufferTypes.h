#pragma once
#include <DirectXMath.h>

struct ConstantVertexBuffer2D
{
    DirectX::XMMATRIX mat;
    DirectX::XMFLOAT2 uv_offset = {0.f, 0.f};
    DirectX::XMFLOAT2 uv_scale = {1.f, 1.f};
};

struct ConstantPixelBuffer2D
{
    float r = 1.f;
    float g = 1.f;
    float b = 1.f;
    float alpha = 1.f;
};

struct ConstantVertexPrimitiveBuffer
{
    DirectX::XMMATRIX mat;
};

struct ConstantPixelPrimitiveBuffer
{
    float r = 1.f;
    float g = 1.f;
    float b = 1.f;
    float alpha = 1.f;
};
