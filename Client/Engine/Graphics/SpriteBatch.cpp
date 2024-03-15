#include "SpriteBatch.h"

#include <d3d11.h>
#include "TempSprite.h"

SpriteBatch::SpriteBatch(ID3D11DeviceContext* device_context)
{
    device_context_ = device_context;
    orthographic_matrix_ = DirectX::XMMatrixIdentity();
}

void SpriteBatch::Begin(DirectX::XMMATRIX orthographic_matrix)
{
    orthographic_matrix_ = orthographic_matrix;
}

void SpriteBatch::End()
{
    orthographic_matrix_ = DirectX::XMMatrixIdentity();
}

void SpriteBatch::Draw(TempSprite* sprite, UINT frame_index)
{
    DirectX::XMMATRIX wvp_matrix = orthographic_matrix_;
}
