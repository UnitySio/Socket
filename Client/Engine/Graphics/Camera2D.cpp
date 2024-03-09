#include "Camera2D.h"

#include "Core.h"

Camera2D::Camera2D()
{
    position_ = {0.0f, 0.0f, 0.0f};
    rotation_ = {0.0f, 0.0f, 0.0f};
    position_vector_ = DirectX::XMLoadFloat3(&position_);
    rotation_vector_ = DirectX::XMLoadFloat3(&rotation_);
    UpdateMatrix();
}

void Camera2D::SetProjectionValues(float size, float near_z, float far_z)
{
    Core* core = Core::Get();

    const float width = static_cast<float>(core->GetResolution().x);
    const float height = static_cast<float>(core->GetResolution().y);
    const float aspect_ratio = width / height;
    const float left = -size * aspect_ratio;
    const float right = size * aspect_ratio;

    orthographic_matrix_ = DirectX::XMMatrixOrthographicOffCenterLH(left, right, -size, size, near_z, far_z);
}

void Camera2D::SetPosition(float x, float y, float z)
{
    position_ = {x, y, z};
    position_vector_ = DirectX::XMLoadFloat3(&position_);
    UpdateMatrix();
}

void Camera2D::SetPosition(const DirectX::XMVECTOR& position)
{
    DirectX::XMStoreFloat3(&position_, position);
    position_vector_ = position;
    UpdateMatrix();
}

void Camera2D::AdjustPosition(float x, float y, float z)
{
    position_.x += x;
    position_.y += y;
    position_.z += z;
    position_vector_ = DirectX::XMLoadFloat3(&position_);
    UpdateMatrix();
}

void Camera2D::AdjustPosition(const DirectX::XMVECTOR& position)
{
    position_vector_ = DirectX::XMVectorAdd(position_vector_, position);
    DirectX::XMStoreFloat3(&position_, position_vector_);
    UpdateMatrix();
}

void Camera2D::SetRotation(float x, float y, float z)
{
    rotation_ = {x, y, z};
    rotation_vector_ = DirectX::XMLoadFloat3(&rotation_);
    UpdateMatrix();
}

void Camera2D::SetRotation(const DirectX::XMVECTOR& rotation)
{
    rotation_vector_ = rotation;
    DirectX::XMStoreFloat3(&rotation_, rotation);
    UpdateMatrix();
}

void Camera2D::AdjustRotation(float x, float y, float z)
{
    rotation_.x += x;
    rotation_.y += y;
    rotation_.z += z;
    rotation_vector_ = DirectX::XMLoadFloat3(&rotation_);
    UpdateMatrix();
}

void Camera2D::AdjustRotation(const DirectX::XMVECTOR& rotation)
{
    rotation_vector_ = DirectX::XMVectorAdd(rotation_vector_, rotation);
    DirectX::XMStoreFloat3(&rotation_, rotation_vector_);
    UpdateMatrix();
}

void Camera2D::UpdateMatrix()
{
    DirectX::XMMATRIX translation_matrix = DirectX::XMMatrixTranslation(-position_.x, -position_.y, 0.f);
    DirectX::XMMATRIX rotation_matrix = DirectX::XMMatrixRotationRollPitchYaw(-rotation_.x, -rotation_.y, -rotation_.z);
    world_matrix_ = rotation_matrix * translation_matrix;
}
