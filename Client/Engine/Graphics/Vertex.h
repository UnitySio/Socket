#pragma once
#include <DirectXMath.h>

struct Vertex
{
    Vertex();
    Vertex(float x, float y) : x(x), y(y) {}

    DirectX::XMFLOAT2 pos;
};
