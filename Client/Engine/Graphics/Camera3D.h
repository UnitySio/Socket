#pragma once
#include <DirectXMath.h>

class Camera3D
{
public:
    Camera3D();
    ~Camera3D() = default;

    void SetProjectionValues(float fov_degrees, float aspect_ratio, float z_near, float z_far);
    void SetPosition(float x, float y, float z);
    void SetPosition(const DirectX::XMVECTOR& position);
    void AdjustPosition(float x, float y, float z);
    void AdjustPosition(const DirectX::XMVECTOR& position);
    void SetRotation(float x, float y, float z);
    void SetRotation(const DirectX::XMVECTOR& rotation);
    void AdjustRotation(float x, float y, float z);
    void AdjustRotation(const DirectX::XMVECTOR& rotation);
    void SetLookAtPos(DirectX::XMFLOAT3 look_at_pos);

    inline const DirectX::XMMATRIX& GetViewMatrix() const { return view_matrix_; }
    inline const DirectX::XMMATRIX& GetProjectionMatrix() const { return projection_matrix_; }
    inline const DirectX::XMVECTOR& GetPositionVector() const { return position_vector_; }
    inline const DirectX::XMVECTOR& GetRotationVector() const { return rotation_vector_; }
    inline const DirectX::XMFLOAT3& GetPosition() const { return position_; }
    inline const DirectX::XMFLOAT3& GetRotation() const { return rotation_; }
    inline const DirectX::XMVECTOR& GetForwardVector() const { return vec_forward_; }
    inline const DirectX::XMVECTOR& GetBackwardVector() const { return vec_backward_; }
    inline const DirectX::XMVECTOR& GetLeftVector() const { return vec_left_; }
    inline const DirectX::XMVECTOR& GetRightVector() const { return vec_right_; }

private:
    void UpdateViewMatrix();

    DirectX::XMVECTOR position_vector_;
    DirectX::XMVECTOR rotation_vector_;

    DirectX::XMFLOAT3 position_;
    DirectX::XMFLOAT3 rotation_;

    DirectX::XMMATRIX view_matrix_;
    DirectX::XMMATRIX projection_matrix_;

    const DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = { 0.0f, 0.0f, 1.0f, 0.0f };
    const DirectX::XMVECTOR DEFAULT_UP_VECTOR = { 0.0f, 1.0f, 0.0f, 0.0f };
    const DirectX::XMVECTOR DEFAULT_BACKWARD_VECTOR = { 0.0f, 0.0f, -1.0f, 0.0f };
    const DirectX::XMVECTOR DEFAULT_LEFT_VECTOR = { -1.0f, 0.0f, 0.0f, 0.0f };
    const DirectX::XMVECTOR DEFAULT_RIGHT_VECTOR = { 1.0f, 0.0f, 0.0f, 0.0f };

    DirectX::XMVECTOR vec_forward_;
    DirectX::XMVECTOR vec_backward_;
    DirectX::XMVECTOR vec_left_;
    DirectX::XMVECTOR vec_right_;
    
};
