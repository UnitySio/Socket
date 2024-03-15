#pragma once
#include <DirectXMath.h>
#include <string>
#include <vector>

#include "ConstantBuffer.h"
#include "ConstantBufferTypes.h"
#include "IndexBuffer.h"
#include "Vertex.h"
#include "VertexBuffer.h"

class Texture;

struct SpriteFrame
{
    float offset_x = 0;
    float offset_y = 0;
    float scale_x = 1;
    float scale_y = 1;
};

class Sprite
{
public:
    Sprite();
    ~Sprite() = default;

    bool Init(ID3D11DeviceContext* device_context, Texture* texture, float ppu,
              ConstantBuffer<ConstantVertexBuffer2D>& constant_buffer,
              ConstantBuffer<ConstantPixelBuffer2D>& constant_pixel_buffer);

    void Draw(DirectX::XMMATRIX orthographic_matrix);
    void SetPosition(float x, float y, float z);
    void SetPosition(const DirectX::XMVECTOR& position);
    void AdjustPosition(float x, float y, float z);
    void AdjustPosition(const DirectX::XMVECTOR& position);
    void SetRotation(float x, float y, float z);
    void SetRotation(const DirectX::XMVECTOR& rotation);
    void AdjustRotation(float x, float y, float z);
    void AdjustRotation(const DirectX::XMVECTOR& rotation);
    void SetScale(float x, float y, float z = 1.f);

    inline const DirectX::XMVECTOR& GetPositionVector() const { return position_vector_; }
    inline const DirectX::XMVECTOR& GetRotationVector() const { return rotation_vector_; }
    inline const DirectX::XMFLOAT3& GetPosition() const { return position_; }
    inline const DirectX::XMFLOAT3& GetRotation() const { return rotation_; }

private:
    void UpdateMatrix();

    ID3D11DeviceContext* device_context_;

    ConstantBuffer<ConstantVertexBuffer2D>* constant_buffer_;
    ConstantBuffer<ConstantPixelBuffer2D>* constant_pixel_buffer_;

    Texture* texture_;

    DirectX::XMVECTOR position_vector_;
    DirectX::XMVECTOR rotation_vector_;

    DirectX::XMFLOAT3 position_;
    DirectX::XMFLOAT3 rotation_;
    DirectX::XMFLOAT3 scale_;

    DirectX::XMMATRIX world_matrix_;

    std::vector<SpriteFrame> frames_;
};
