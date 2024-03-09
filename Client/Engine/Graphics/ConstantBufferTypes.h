#pragma once
#include <DirectXMath.h>

struct ConstantVertexBuffer3D
{
    DirectX::XMMATRIX mat;
};

struct ConstantVertexBuffer2D
{
    DirectX::XMMATRIX mat;
};

struct ConstantPixelBuffer3D
{
    float alpha = 1.f;
};

struct ConstantPixelBuffer2D
{
    float r = 1.f;
    float g = 1.f;
    float b = 1.f;
    float alpha = 1.f;
};
