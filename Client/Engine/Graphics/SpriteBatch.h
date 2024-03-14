#pragma once
#include <DirectXMath.h>
#include <intsafe.h>

class ID3D11DeviceContext;

class SpriteBatch
{
public:
    SpriteBatch(ID3D11DeviceContext* device_context);
    ~SpriteBatch() = default;

    void Begin(DirectX::XMMATRIX orthographic_matrix);
    void End();
    void Draw(class Sprite* sprite, UINT frame_index = 0);

private:
    ID3D11DeviceContext* device_context_;

    DirectX::XMMATRIX orthographic_matrix_;
    
};
