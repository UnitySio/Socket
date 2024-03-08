#pragma once
#include <DirectXMath.h>

struct Vertex
{
    Vertex();
    Vertex(float x, float y, float z, float u, float v) : pos(x, y, z), texcoord(u, v) {}

    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT2 texcoord;
};

struct Vertex2D
{
    Vertex2D();
    Vertex2D(float x, float y, float z, float u, float v) : pos(x, y, z), texcoord(u, v) {}

    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT2 texcoord;
};
