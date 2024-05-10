#pragma once
#include <DirectXMath.h>

struct DefaultVertex
{
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT4 color;
    DirectX::XMFLOAT2 texcoord = { -1.f, -1.f };
};
