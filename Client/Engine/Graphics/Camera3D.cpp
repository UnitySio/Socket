#include "Camera3D.h"

Camera3D::Camera3D()
{
    position_ = {0.0f, 0.0f, 0.0f};
    rotation_ = {0.0f, 0.0f, 0.0f};
    position_vector_ = DirectX::XMLoadFloat3(&position_);
    rotation_vector_ = DirectX::XMLoadFloat3(&rotation_);
    UpdateViewMatrix();
}

void Camera3D::SetProjectionValues(float fov_degrees, float aspect_ratio, float z_near, float z_far)
{
    const float fov_radians = (fov_degrees / 360.0f) * DirectX::XM_2PI;
    projection_matrix_ = DirectX::XMMatrixPerspectiveFovLH(fov_radians, aspect_ratio, z_near, z_far);
}

void Camera3D::SetPosition(float x, float y, float z)
{
    position_ = {x, y, z};
    position_vector_ = DirectX::XMLoadFloat3(&position_);
    UpdateViewMatrix();
}

void Camera3D::SetPosition(const DirectX::XMVECTOR& position)
{
    DirectX::XMStoreFloat3(&position_, position);
    position_vector_ = position;
    UpdateViewMatrix();
}

void Camera3D::AdjustPosition(float x, float y, float z)
{
    position_.x += x;
    position_.y += y;
    position_.z += z;
    position_vector_ = DirectX::XMLoadFloat3(&position_);
    UpdateViewMatrix();
}

void Camera3D::AdjustPosition(const DirectX::XMVECTOR& position)
{
    position_vector_ = DirectX::XMVectorAdd(position_vector_, position);
    DirectX::XMStoreFloat3(&position_, position_vector_);
    UpdateViewMatrix();
}

void Camera3D::SetRotation(float x, float y, float z)
{
    rotation_ = {x, y, z};
    rotation_vector_ = DirectX::XMLoadFloat3(&rotation_);
    UpdateViewMatrix();
}

void Camera3D::SetRotation(const DirectX::XMVECTOR& rotation)
{
    rotation_vector_ = rotation;
    DirectX::XMStoreFloat3(&rotation_, rotation);
    UpdateViewMatrix();
}

void Camera3D::AdjustRotation(float x, float y, float z)
{
    rotation_.x += x;
    rotation_.y += y;
    rotation_.z += z;
    rotation_vector_ = DirectX::XMLoadFloat3(&rotation_);
    UpdateViewMatrix();
}

void Camera3D::AdjustRotation(const DirectX::XMVECTOR& rotation)
{
    rotation_vector_ = DirectX::XMVectorAdd(rotation_vector_, rotation);
    DirectX::XMStoreFloat3(&rotation_, rotation_vector_);
    UpdateViewMatrix();
}

void Camera3D::SetLookAtPos(DirectX::XMFLOAT3 look_at_pos)
{
    if (look_at_pos.x == position_.x && look_at_pos.y == position_.y && look_at_pos.z == position_.z) return;

    look_at_pos.x = position_.x - look_at_pos.x;
    look_at_pos.y = position_.y - look_at_pos.y;
    look_at_pos.z = position_.z - look_at_pos.z;

    float pitch = 0.f;
    if (look_at_pos.y != 0.f)
    {
        const float distance = sqrt(look_at_pos.x * look_at_pos.x + look_at_pos.z * look_at_pos.z);
        pitch = atan(look_at_pos.y / distance);
    }

    float yaw = 0.f;
    if (look_at_pos.x != 0.f)
    {
        yaw = atan(look_at_pos.x / look_at_pos.z);
    }

    if (look_at_pos.z > 0) yaw += DirectX::XM_PI;

    SetRotation(pitch, yaw, 0.f);
}

void Camera3D::UpdateViewMatrix()
{
    const DirectX::XMMATRIX rot_matrix = DirectX::XMMatrixRotationRollPitchYaw(rotation_.x, rotation_.y, rotation_.z);
    DirectX::XMVECTOR target = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, rot_matrix);
    target = DirectX::XMVectorAdd(position_vector_, target);

    DirectX::XMVECTOR up_dir = DirectX::XMVector3TransformCoord(DEFAULT_UP_VECTOR, rot_matrix);
    view_matrix_ = DirectX::XMMatrixLookAtLH(position_vector_, target, up_dir);

    DirectX::XMMATRIX vec_rot_matrix = DirectX::XMMatrixRotationRollPitchYaw(0.f, rotation_.y, 0.f);
    vec_forward_ = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, vec_rot_matrix);
    vec_backward_ = DirectX::XMVector3TransformCoord(DEFAULT_BACKWARD_VECTOR, vec_rot_matrix);
    vec_left_ = DirectX::XMVector3TransformCoord(DEFAULT_LEFT_VECTOR, vec_rot_matrix);
    vec_right_ = DirectX::XMVector3TransformCoord(DEFAULT_RIGHT_VECTOR, vec_rot_matrix);
}
