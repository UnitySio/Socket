#pragma once
#include <DirectXMath.h>

class Camera2D
{
public:
    Camera2D();
    ~Camera2D() = default;

    void SetProjectionValues(float width, float height, float near_z, float far_z);
    void SetPosition(float x, float y, float z);
    void SetPosition(const DirectX::XMVECTOR& position);
    void AdjustPosition(float x, float y, float z);
    void AdjustPosition(const DirectX::XMVECTOR& position);
    void SetRotation(float x, float y, float z);
    void SetRotation(const DirectX::XMVECTOR& rotation);
    void AdjustRotation(float x, float y, float z);
    void AdjustRotation(const DirectX::XMVECTOR& rotation);

    inline const DirectX::XMMATRIX& GetOrthographicMatrix() const { return orthographic_matrix_; }
    inline const DirectX::XMMATRIX& GetWorldMatrix() const { return world_matrix_; }
    inline const DirectX::XMVECTOR& GetPositionVector() const { return position_vector_; }
    inline const DirectX::XMVECTOR& GetRotationVector() const { return rotation_vector_; }
    inline const DirectX::XMFLOAT3& GetPosition() const { return position_; }
    inline const DirectX::XMFLOAT3& GetRotation() const { return rotation_; }

private:
    void UpdateMatrix();

    DirectX::XMMATRIX orthographic_matrix_;
    DirectX::XMMATRIX world_matrix_;
    
    DirectX::XMVECTOR position_vector_;
    DirectX::XMVECTOR rotation_vector_;

    DirectX::XMFLOAT3 position_;
    DirectX::XMFLOAT3 rotation_;
    
};
