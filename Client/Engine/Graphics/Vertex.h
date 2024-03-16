#pragma once
#include <DirectXMath.h>

struct Vertex2D
{
    Vertex2D();

    Vertex2D(float x, float y, float z, float u, float v) : pos(x, y, z), texcoord(u, v)
    {
    }

    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT2 texcoord;
};

struct VertexPrimitive
{
    VertexPrimitive();

    VertexPrimitive(float x, float y, float z, float r, float g, float b, float a) : pos(x, y, z), color(r, g, b, a)
    {
    }

    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT4 color;
};
